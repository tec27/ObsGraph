#include <windows.h>
#include "BWAddresses.h"

/*
procedure PeekMem(Address: Cardinal; Buffer: Pointer; Size: Cardinal);
var
  {ThrowawayVar: Cardinal;}
  I: Integer;
begin
  {ReadProcessMemory(SCProcHandle, Pointer(Address), Buffer,
                      Size, ThrowawayVar);}
  for I := 0 to Size - 1 do
  begin
    PByte(Cardinal(Buffer) + Cardinal(I))^ := PByte(Address + Cardinal(I))^;
  end;
end;
*/
void PeekMem(DWORD address, void * buffer, DWORD size)
{
	for(int i = 0; (DWORD)i < size; i++) {
		((byte *)buffer)[i] = ((byte *)address)[i];
	}
}

/*
procedure PokeMem(Address: Cardinal; Buffer: Pointer; Size: Cardinal);
var
  {ThrowawayVar: Cardinal;}
  I: Integer;
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
begin
  {WriteProcessMemory(SCProcHandle,Pointer(Address),Buffer,Size,ThrowawayVar);}
  for I := 0 to Size - 1 do
  begin
    WriteMem(Address+Cardinal(I),Cardinal(Buffer)+Cardinal(I),1);
  end;
end;
*/
void WriteMem(DWORD MemOffset, DWORD DataPtr, DWORD DataLen) {
	DWORD OldProt, OldProt2;

	VirtualProtect((LPVOID)MemOffset, (SIZE_T)DataLen, PAGE_EXECUTE_READWRITE, &OldProt);
	VirtualProtect((LPVOID)DataPtr, (SIZE_T)DataLen, PAGE_EXECUTE_READWRITE, &OldProt2);
	CopyMemory((LPVOID)MemOffset, (LPVOID)DataPtr, DataLen);
	VirtualProtect((LPVOID)DataPtr, DataLen, OldProt2, &OldProt2);
	VirtualProtect((LPVOID)MemOffset, DataLen, OldProt, &OldProt);
}

void PokeMem(DWORD address, void * buffer, DWORD size)
{
	for(int i = 0; (DWORD)i < size; i++) {
		WriteMem(address+i, (DWORD)buffer, 1);
	}
}

/*
function ReadMapPath: string;
var
  tempChar: Char;
  chOffset: Cardinal;
begin
  Result := '';
  chOffSet := 0;
  repeat
    PeekMem(Offsets.MapFilePath+chOffset,@tempChar,sizeof(Char));
    Result := Result + tempChar;
    Inc(chOffset);
  until tempChar = #0;
  Result := Trim(Result);
end;
*/
char * ReadMapPath()
{
	char * retVal = (char *)malloc(strlen((char *)MAP_FILE_PATH)+1);
	int chOffset = 0;
	char tempChar;
	do {
		PeekMem(MAP_FILE_PATH + chOffset, &tempChar, sizeof(char));
		retVal[chOffset++] = tempChar; 
	} while(tempChar != 0);
	
	return retVal;
}

/*
function ReadSavedRepName: string;
var
  tempChar: Char;
  chOffset: Cardinal;
begin
  Result := '';
  chOffSet := 0;
  repeat
    PeekMem(Offsets.SavedRepName+chOffset,@tempChar,sizeof(Char));
    Result := Result + tempChar;
    Inc(chOffset);
  until tempChar = #0;
  Result := Trim(Result);
end;
*/
char * ReadSavedRepName()
{
	char * retVal = (char *)malloc(strlen((char *)SAVED_REP_NAME)+1);
	int chOffset = 0;
	char tempChar;
	do {
		PeekMem(SAVED_REP_NAME + chOffset, &tempChar, sizeof(char));
		retVal[chOffset++] = tempChar; 
	} while(tempChar != 0);
	
	return retVal;
}

/*
function IsInReplay: Boolean;
var
  InRepByte: Byte;
begin
  PeekMem(Offsets.InReplay,@InRepByte,1);
  Result := (InRepByte > 0) and IsInGame;
end;
*/
bool IsInReplay() {
	return *((bool *)IN_REPLAY);
}

/*
function IsInGame: Boolean;
var
  InGameByte: Byte;
begin
  PeekMem(Offsets.InGame,@InGameByte,sizeof(Byte));
  Result := (InGameByte = 1); // should be 1 for both replay and game
end;
*/
bool IsInGame()
{
	return *((bool *)IN_GAME);
}

/*
function IsPaused: Boolean;
var
  IsRepPaused, IsGamePaused: Byte;
begin
  if IsInReplay then
  begin
    PeekMem(Offsets.RepPaused,@IsRepPaused,1);
    PeekMem(Offsets.GamePaused,@IsGamePaused,1);
    Result := (IsRepPaused or IsGamePaused) = 1;
  end
  else
  begin
    PeekMem(Offsets.GamePaused,@IsGamePaused,1);
    Result := (IsGamePaused = 1);
  end;
end;
*/
bool IsPaused()
{
	if(IsInReplay())
		return *((bool *)GAME_PAUSED) || *((bool *)REP_PAUSED);
	else
		return *((bool *)GAME_PAUSED); 
}

/*
function IsGameComplete: Boolean;
var
  IsComplete: Byte;
begin
  PeekMem(Offsets.GameCompleteDlg,@IsComplete,1);
  Result := IsComplete = 1;
end;
*/
bool IsGameComplete()
{
	return *((bool *)GAME_COMPLETE_DIALOG); 
}

/*
function GetPNum: Integer;
begin
  if IsInReplay then
  begin
    Result := Integer(Pointer(Offsets.RepSelectedPlayer)^);
    if Result > 11 then
      Result := -1;
  end
  else
    Result := Integer(Pointer(Offsets.MyPNumAddr)^);
end;
*/
int GetPNum()
{
	if(IsInReplay()) {
		int result = *(int *)REP_SELECTED_PLAYER;
		if(result > 11)
			return -1;
	}
	else
		return *(int *)MY_PLAYER_NUM;
}

/*
function GetPlayerName(Player: byte): string; // Thanks MoC
begin
  SetLength(Result,24);
  Move(Pointer(Offsets.PlayerNames+36*Player)^,Result[1],Length(Result));
  FitZeroTerminatedString(Result);
end;
*/
char * GetPlayerName(byte player)
{
	char * retVal = (char *)malloc(strlen((char *)PLAYER_NAMES + (36*player))+1);
	MoveMemory((void *)(PLAYER_NAMES+(36*player)), retVal, strlen((char *)PLAYER_NAMES + (36*player))+1);
	
	return retVal;
}

/*
function GetCurTextFormat: Cardinal;
begin
  PeekMem(Offsets.CurTextFormat,@Result,4);
end;
*/
DWORD GetCurTextFormat()
{
	return *(DWORD *)CUR_TEXT_FORMAT;
}

/*
function GetBuildingsControlled(Player: Byte): Integer;
begin
  PeekMem((Player*4)+Offsets.BuildingsControlled,@Result,4);
end;
*/
int GetBuildingsControlled(byte player)
{
	return *(int *)((player*4) + BUILDINGS_CONTROLLED);
}

/*
function GetPopulation(Player: Byte): Integer;
begin
  PeekMem((Player*4)+Offsets.Population,@Result,4);
end;
*/
int GetPopulation(byte player)
{
	return *(int *)((player*4) + POPULATION);
}

/*
function GetMinerals(Player: Byte): Integer;
begin
  PeekMem((Player*4)+Offsets.Minerals,@Result,4);
end;
*/
int GetMinerals(byte player)
{
	return *(int *)((player*4) + MINERALS);
}

/*
function GetVespene(Player: Byte): Integer;
begin
  PeekMem((Player*4)+Offsets.Vespene,@Result,4);
end;
*/
int GetVespene(byte player)
{
	return *(int *)((player*4) + VESPENE);
}

/*
function IsObsMode: Boolean;
var
  PNum: Byte;
begin
  // we need to handle both initial obs, and "almost dead" obs
  // we also need to try to avoid annoying/hacky UMS obs accidents
  // so the conditions are: (buildings <= 1 and units <= 2 and minerals <= 50 and vespenes == 0)
  // or (buildings <= 1 and units == 0)
  PNum := Byte(GetPNum);
  if GetPNum = -1 then
    Result := IsInReplay
  else
    Result := ( (GetBuildingsControlled(PNum)<=1) and (GetPopulation(PNum)<=2) // init obs
                      and (GetMinerals(PNum)<=50) and (GetVespene(PNum)=0) )
              or ( (GetBuildingsControlled(PNum)<=1) and (GetPopulation(PNum)=0) ) // almost dead 'obs'
              or (IsInReplay);
end;
*/
bool IsObsMode()
{
	// we need to handle both initial obs, and "almost dead" obs
	// we also need to try to avoid annoying/hacky UMS obs accidents
	// so the conditions are: (buildings <= 1 and units <= 2 and minerals <= 50 and vespenes == 0)
	// or (buildings <= 1 and units == 0)
	byte PNum = (byte)GetPNum();
	if(GetPNum() == -1)
		return IsInReplay();
	else
		return ( (GetBuildingsControlled(PNum)<=1) && (GetPopulation(PNum)<=2)
					&& (GetMinerals(PNum)<=50) && (GetVespene(PNum)==0) )
				|| ( (GetBuildingsControlled(PNum)<=1) && (GetPopulation(PNum)==0) )
				|| (IsInReplay());
}

/*
function ColorToColorCode(Color:byte):char;
begin
  case Color of
    $6F:result:=#$08;
    $A5:result:=#$0E;
    $9F:result:=#$0F;
    $A4:result:=#$10;
    $9C:result:=#$11;
    $13:result:=#$15;
    $54:result:=#$16;
    $87:result:=#$17;
    $B9:result:=#$18;
    $88:result:=#$19;
    $86:result:=#$1B;
    $33:result:=#$1C;
    $4D:result:=#$1D;
    $9A:result:=#$1E;
    $80:result:=#$1F;
    else result:=#2;
  end;
end;
*/
char ColorToColorCode(byte color) 
{
	switch(color) {
		case 0x6F: return 0x08;
		case 0xA5: return 0x0E;
		case 0x9F: return 0x0F;
		case 0xA4: return 0x10;
		case 0x9C: return 0x11;
		case 0x13: return 0x15;
		case 0x54: return 0x16;
		case 0x87: return 0x17;
		case 0xB9: return 0x18;
		case 0x88: return 0x19;
		case 0x86: return 0x1B;
		case 0x33: return 0x1C;
		case 0x4D: return 0x1D;
		case 0x9A: return 0x1E;
		case 0x80: return 0x1F;
		default: return 0x02;
	}
}

/*
function FactionColor(Faction:byte):byte;
begin
  result:=PByte(Offsets.PlayerColors+Faction)^;
end;
*/
byte GetFactionColor(byte faction)
{
	return *(byte *)(PLAYER_COLORS + faction);
}

/*
function FactionColorCode(Faction:byte):char;
begin
  result:=ColorToColorCode(FactionColor(Faction));
end;
*/
char GetFactionColorCode(byte faction)
{
	return ColorToColorCode(GetFactionColor(faction));
}

/*
function GetPlayerFaction(Player:byte):byte;
begin
  result:=Player;//PByte(Addresses.PlayerNames-1+36*Player)^;
end;
*/
byte GetPlayerFaction(byte player) {
	return player;//*(byte *)(PLAYER_NAMES-1 + 36*player);
}

/*
function GetColoredPlayerName(Player:byte):String;
begin
  result:=FactionColorCode(GetPlayerFaction(Player))+GetPlayerName(Player);
end;
*/
char * GetColoredPlayerName(byte player)
{
	char * retVal = (char *)malloc(strlen((char *)PLAYER_NAMES + (36*player))+2);
	retVal[0] = GetFactionColorCode(GetPlayerFaction(player));
	MoveMemory((void *)(PLAYER_NAMES+(36*player)), retVal+1, strlen((char *)PLAYER_NAMES + (36*player))+1);
	
	return retVal;
}