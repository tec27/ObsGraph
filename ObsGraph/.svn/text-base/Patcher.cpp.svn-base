#include <windows.h>
#include "Patcher.h"

Patcher::Patcher()
{
	patched = false;
	
	patchedArr = (PPatchedJmp*)malloc(sizeof(PPatchedJmp));
	patchArrSize = 1;
	patchArrPos = 0;
	
	patchedMemArr = (PPatchedMem*)malloc(sizeof(PPatchedMem));
	patchMemSize = 1;
	patchMemPos = 0;
}

Patcher::~Patcher()
{
	for(int i = 0; i < patchArrPos; i++) {
		free(patchedArr[i]->newMemory);
		free(patchedArr[i]->origMemory);
		free(patchedArr[i]);
	}
	free(patchedArr);
	
	for(int i = 0; i < patchMemPos; i++) {
		free(patchedMemArr[i]->newMemory);
		free(patchedMemArr[i]->origMemory);
		free(patchedMemArr[i]);
	}
	free(patchedMemArr);
}

/*
procedure WriteMem(MemOffset, DataPtr, DataLen: DWORD); stdcall;
var
  OldProt, OldProt2: DWORD;
begin
  VirtualProtect(Pointer(MemOffset), DataLen, PAGE_EXECUTE_READWRITE, @OldProt);
	VirtualProtect(Pointer(DataPtr), DataLen, PAGE_EXECUTE_READWRITE, @OldProt2);
  CopyMemory(Pointer(MemOffset), Pointer(DataPtr), DataLen);
	VirtualProtect(Pointer(DataPtr), DataLen, OldProt2, @OldProt2);
	VirtualProtect(Pointer(MemOffset), DataLen, OldProt, @OldProt);
end;
*/
void Patcher::WriteMem(DWORD MemOffset, DWORD DataPtr, DWORD DataLen) {
	DWORD OldProt, OldProt2;

	VirtualProtect((LPVOID)MemOffset, (SIZE_T)DataLen, PAGE_EXECUTE_READWRITE, &OldProt);
	VirtualProtect((LPVOID)DataPtr, (SIZE_T)DataLen, PAGE_EXECUTE_READWRITE, &OldProt2);
	CopyMemory((LPVOID)MemOffset, (LPVOID)DataPtr, DataLen);
	VirtualProtect((LPVOID)DataPtr, DataLen, OldProt2, &OldProt2);
	VirtualProtect((LPVOID)MemOffset, DataLen, OldProt, &OldProt);
}

/*
procedure JmpPatch(Location, JumpTo: DWORD); stdcall;
var
  lgJmp: array[0..4] of Byte;
begin
  lgJmp[0] := $E9;
  WriteLn('Creating Jump Patch at: 0x' + IntToHex(Location,8) + ' to: 0x' +
            IntToHex(JumpTo,8) + ' [ 0x' + IntToHex((JumpTo - Location) - 5,8)
            + ']');
  PDWORD(@lgJmp[1])^ := (JumpTo - Location) - 5;
  WriteMem(Location, DWORD(@lgJmp), 5);
end;
*/
void Patcher::JmpPatch(DWORD Location, DWORD JumpTo) {
	unsigned char* lgJmp = (unsigned char*)malloc(5);
	lgJmp[0] = 0xE9;
	*((PDWORD)&lgJmp[1]) = (JumpTo - Location) - 5;
	WriteMem(Location, (DWORD)lgJmp, 5);
	free(lgJmp);
}

/*
procedure CallPatch(Location, CallTo: DWORD); stdcall;
var
  lgCall: array[0..4] of Byte;
begin
  lgCall[0] := $E8;
  WriteLn('Creating Call Patch at: 0x' + IntToHex(Location,8) + ' to: 0x' +
            IntToHex(CallTo,8) + ' [ 0x' + IntToHex((CallTo - Location) - 5,8)
            + ']');
  PDWORD(@lgCall[1])^ := (CallTo - Location) - 5;
  WriteMem(Location, DWORD(@lgCall), 5);
end;
*/
void Patcher::CallPatch(DWORD Location, DWORD CallTo) {
	unsigned char* lgCall = (unsigned char*)malloc(5);
	lgCall[0] = 0xE8;
	*((PDWORD)&lgCall[1]) = (CallTo - Location) - 5;
	WriteMem(Location, (DWORD)lgCall, 5);
	free(lgCall);
}

/*
procedure AddPatch(dAddr,dJmpTo: DWORD; NumNops: Integer = 0);
var
  I: Integer;
  WorkingAddr: Cardinal;
  OldProt: DWORD;
begin
  SetLength(PatchedArr,Length(PatchedArr)+1);
  with PatchedArr[Length(PatchedArr)-1] do
  begin
    Addr := dAddr;
    JmpTo := dJmpTo;
    SetLength(OrigMemory,5+NumNops); // Overwriting + new Jump/Call sled
    SetLength(NewMemory,15+NumNops);
    VirtualProtect(@NewMemory[0], Length(NewMemory), PAGE_EXECUTE_READWRITE, @OldProt);
    for I := 0 to Length(OrigMemory) - 1 do
    begin
        OrigMemory[I] := PBYTE(Addr+Cardinal(I))^;
        NewMemory[I] := OrigMemory[I];
        WriteLn('Copied byte from [0x' + IntToHex(Addr+Cardinal(I),8) + ']: 0x' +
          IntToHex(OrigMemory[I],2));
    end;

    // handle redirecting jmps/calls
    if (NewMemory[0] = $E8) or (NewMemory[0] = $E9) then
    begin
      WorkingAddr := PDword(@NewMemory[1])^ + Addr + 5;
      WriteLn('Reworking Call/Jmp to: 0x' + IntToHex(WorkingAddr,8));
      PDword(@NewMemory[1])^ := (WorkingAddr - Cardinal(@NewMemory[0])) - 5;
    end;

    WorkingAddr := Cardinal(@NewMemory[0]) + Cardinal(5 + NumNops);
    CallPatch(WorkingAddr,JmpTo); // Call our hooking function
    WorkingAddr := WorkingAddr + 5;
    JmpPatch(WorkingAddr, Addr + Cardinal(5 + NumNops)); // Jump back right past where we overwrite
  end;
end;
*/
void Patcher::AddPatch(DWORD dAddr, DWORD dJmpTo, int numNops)
{
	if(patchArrPos == patchArrSize) {
		// resize needed
		PPatchedJmp* oldArray = patchedArr;
		int newSize = patchArrSize * 2;
		patchedArr = (PPatchedJmp*)malloc(newSize * sizeof(PPatchedJmp));
		for(int i = 0; i < patchArrSize; i++) {
			patchedArr[i] = oldArray[i];
		}
		patchArrSize = newSize;
		
		free(oldArray);
	}
		
	PatchedJmp * newPatch = (PatchedJmp *)malloc(sizeof(PatchedJmp));
	newPatch->addr = dAddr;
	newPatch->jmpTo = dJmpTo;
	newPatch->numNops = numNops;
	newPatch->origMemory = (byte *)malloc(5+numNops);
	newPatch->newMemory = (byte *)malloc(15+numNops);
	DWORD OldProt;
	VirtualProtect((LPVOID)newPatch->newMemory, 15+numNops, PAGE_EXECUTE_READWRITE, &OldProt); // make our sled executable
	for(int i = 0; i < 5+numNops; i++) {
		newPatch->origMemory[i] = *(byte *)(newPatch->addr + i);
		newPatch->newMemory[i] = newPatch->origMemory[i];
	}
		
    //handle redirecting jmps/calls
    DWORD workingAddr;
    if((newPatch->newMemory[0] == 0xE8) || (newPatch->newMemory[0] == 0xE9)) {
		workingAddr = *(DWORD *)(&newPatch->newMemory[1]);
		workingAddr += newPatch->addr + 5;
		*(DWORD *)(&newPatch->newMemory[1]) = (workingAddr - (DWORD)(newPatch->newMemory)) - 5;
    }
    
   
    
    workingAddr = (DWORD)(&newPatch->newMemory[0]) + 5 + numNops;
    CallPatch(workingAddr, newPatch->jmpTo); // Call our hooking function    
    workingAddr += 5;
    JmpPatch(workingAddr, newPatch->addr + 5 + numNops); // Jump back right past where we overwrite
     
    patchedArr[patchArrPos++] = newPatch;
    
}

/*
procedure AddPatchedMem(dAddr: DWORD; NewMem: array of Byte);
var
  I: Integer;
begin
  SetLength(PatchedMemArr,Length(PatchedMemArr)+1);
  with PatchedMemArr[Length(PatchedMemArr)-1] do
  begin
    Addr := dAddr;
    SetLength(NewMemory, Length(NewMem));
    for I := 0 to Length(NewMem) - 1 do
      NewMemory[I] := NewMem[I];

    SetLength(OrigMemory,Length(NewMemory));
    for I := 0 to Length(OrigMemory) - 1 do
    begin
      OrigMemory[I] := Byte((Pointer(dAddr+Cardinal(I)))^);
    end;
  end;
end;
*/
void Patcher::AddPatchedMem(DWORD dAddr, byte *newMem, int memLength)
{
	if(patchMemPos == patchMemSize) {
		// resize needed
		PPatchedMem* oldArray = patchedMemArr;
		int newSize = patchMemSize * 2;
		patchedMemArr = (PPatchedMem*)malloc(newSize * sizeof(PPatchedMem));
		for(int i = 0; i < patchMemSize; i++) {
			patchedMemArr[i] = oldArray[i];
		}
		patchMemSize = newSize;
		
		free(oldArray);
	}
	
	PatchedMem * newPatch = (PatchedMem *)malloc(sizeof(PatchedMem));
	newPatch->addr = dAddr;
	newPatch->memLength = memLength;
	newPatch->newMemory = (byte *)malloc(memLength);
	for(int i = 0; i < memLength; i++)
		newPatch->newMemory[i] = newMem[i];
	
	newPatch->origMemory = (byte *)malloc(memLength);
	for(int i = 0; i < memLength; i++)
		newPatch->origMemory[i] = *(byte *)(dAddr+i);
		
	patchedMemArr[patchMemPos++] = newPatch;
}

/*
procedure Patch;
const
  Nop: Byte = $90;
var
  I,J: Integer;
begin
  for I := 0 to Length(PatchedArr) - 1 do
  begin
    with PatchedArr[I] do
    begin
      JmpPatch(Addr,Cardinal(@NewMemory[0]));

      if Length(OrigMemory) > 5 then
      begin
        for J := 5 to Length(OrigMemory) - 1 do
           WriteMem(Addr+Cardinal(J),Cardinal(@Nop),1);
      end;
    end;
  end;

  for I := 0 to Length(PatchedMemArr) - 1 do
  begin
    with PatchedMemArr[I] do
    begin
      for J := 0 to Length(NewMemory) - 1 do
      begin
        WriteMem(Addr+Cardinal(J),Cardinal(@NewMemory[J]),1);
      end;
    end;
  end;

  Patched := True;
end;
*/
void Patcher::Patch()
{
	const unsigned char Nop = 0x90;
			
	for(int i = 0; i < patchArrPos; i++) {
		JmpPatch(patchedArr[i]->addr,(DWORD)patchedArr[i]->newMemory);
				
		for(int j = 0; j < patchedArr[i]->numNops; j++) {
			WriteMem(patchedArr[i]->addr+j+5,(DWORD)&Nop,1);
		}
	}
	
	for(int i = 0; i < patchMemPos; i++) {
		WriteMem(patchedMemArr[i]->addr, (DWORD)&patchedMemArr[i]->newMemory[0], patchedMemArr[i]->memLength);
		//for(int j = 0; j < patchedMemArr[i]->memLength; j++) {
		//	WriteMem(patchedMemArr[i]->addr + j, (DWORD)&patchedMemArr[i]->newMemory[j],1);
		//}
	}
		
	patched = true;
}

/*
procedure Unpatch;
var
  I, J: Integer;
begin
  for I := 0 to Length(PatchedArr) - 1 do
  begin
    with PatchedArr[I] do
    begin
      for J := 0 to Length(OrigMemory) - 1 do
      begin
        WriteMem(Addr+Cardinal(J),Cardinal(@OrigMemory[J]),1);
      end;
    end;
  end;

  for I := 0 to Length(PatchedMemArr) - 1 do
  begin
    with PatchedMemArr[I] do
    begin
      for J := 0 to Length(OrigMemory) - 1 do
      begin
        WriteMem(Addr+Cardinal(J),Cardinal(@OrigMemory[J]),1);
      end;
    end;
  end;

  Patched := False;
end;
*/
void Patcher::Unpatch()
{
	for(int i = 0; i < patchArrPos; i++) {
		WriteMem(patchedArr[i]->addr, (DWORD)patchedArr[i]->origMemory, 5 + patchedArr[i]->numNops);
		//for(int j = 0; j < patchedArr[i]->numNops+5; j++) {
		//	WriteMem(patchedArr[i]->addr+j, (DWORD)patchedArr[i]->origMemory[j], 1);
		//}
	}
	
	for(int i = 0; i < patchMemPos; i++) {
		WriteMem(patchedMemArr[i]->addr, (DWORD)patchedMemArr[i]->origMemory, patchedMemArr[i]->memLength);
		//for(int j = 0; j < patchedMemArr[i]->memLength; j++) {
		//	WriteMem(patchedMemArr[i]->addr+j, (DWORD)patchedMemArr[i]->origMemory[j], 1);
		//}
	}
	
	patched = false;
}
