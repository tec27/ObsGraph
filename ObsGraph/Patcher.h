#ifndef PATCHER_H
#define PATCHER_H

/*
  TPatchedJmp = packed record
    Addr: DWORD;
    JmpTo: DWORD;
    OrigMemory: array of Byte;
    NewMemory: array of Byte;
  end;
*/
#pragma pack(1)
struct PatchedJmp {
	DWORD addr;
	DWORD jmpTo;
	int numNops;
	byte* origMemory;
	byte* newMemory;
};
typedef PatchedJmp * PPatchedJmp;

/*
  TPatchedMem = record
    Addr: DWORD;
    OrigMemory: array of Byte;
    NewMemory: array of Byte;
  end;
*/
struct PatchedMem {
	DWORD addr;
	int memLength;
	byte* origMemory;
	byte* newMemory;
};
typedef PatchedMem * PPatchedMem;

/*
procedure AddPatch(dAddr,dJmpTo: DWORD; NumNops: Integer = 0);
procedure AddPatchedMem(dAddr: DWORD; NewMem: array of Byte);
procedure Patch;
procedure Unpatch;
*/

/*
var
  Patched: Boolean;
  PatchedArr: array of TPatchedJmp;
  PatchedMemArr: array of TPatchedMem;
*/


class Patcher {

	public:

		Patcher();
		~Patcher();

		void AddPatch(DWORD dAddr, DWORD dJmpTo, int numNops = 0);
		void AddPatchedMem(DWORD dAddr, byte* newMem, int memLength);
		void Patch();
		void Unpatch();
		bool isPatched() { return patched; }
	
	private:
		void WriteMem(DWORD MemOffset, DWORD DataPtr, DWORD DataLen);
		void JmpPatch(DWORD Location, DWORD JumpTo);
		void CallPatch(DWORD Location, DWORD CallTo);
		bool patched;
		PPatchedJmp* patchedArr;
		int patchArrSize, patchArrPos;
		PPatchedMem* patchedMemArr;
		int patchMemSize, patchMemPos;

}; //class
#endif