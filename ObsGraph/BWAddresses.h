#ifndef BWADDRESSES_H
#define BWADDRESSES_H

#include <windows.h>

// define the version number here
#define V1161

/*
var
  Offsets: TOffsets;
  SCProcHandle: THandle = 0;
  SCWnd: THandle = 0;

const
  Offsets1161: TOffsets = (
    InReplay: $006D0F14; // Byte -- Need to use this with InGame to determine
    InGame: $006D11EC; // Byte
    DebriefingRoom: $006D63C0; // Byte, = 1 if they're currently viewing the 'scores room' after the game
    MapFilePath: $0057FD3C; // string
    SavedRepName: $0051BFB8; // string, contains name used in rep saving without '.rep'
    GameTime: $0057F23C; // Dword
    RepSpeed: $006CDFD4; // byte, 6 for fastest
    RepSpeedMultiplier: $0050E058; // byte, x2 = 2, x4 = 4, etc.
    RepSpeedTiming: $005124F0; // byte, stores time for each frame, 42ms for fastest
    RepPaused: $006D11B0; // Byte
    GamePaused: $006509C4; // Byte
    GameCompleteDlg: $00685178; // Byte, tells whether the "Exit Replay"/"Continue Playing" dlg is up
    GameDigitalVolume: $006CDFE4; // Byte, 0-100 for percent volume
    TickTimeTable: $005124D8; // Table of DWords giving actual timings for speeds <= Fastest (Dwords)
    RepSelectedPlayer: $005153F8; // -1 if nothing is selected, otherwise player #
    PlayerNames: $0057EEEB; // 36 Bytes per player, first 24 are the string
    BuildingsControlled: $00581F34; // DW, +4*Player
    Population: $00581E14; // DW, +4*Player
    Minerals: $0057F0F0; //DW, +4*Player
    Vespene: $0057F120; //DW, +4*Player
    MyPNumAddr: $00512684; // Current Player's number
    CursorX: $006CDDC4; // DW, X coord of the mouse cursor ingame
    CursorY: $006CDDC8; // DW, Y coord of the mouse cursor ingame
    PlayerColors: $00581DD6; // array of player colors
    CurTextFormat: $006D5DDC; // DW, the current font the text is in
    bwtf_Reset: $00000000;
    bwtf_UltraLarge: $006CE100;
    bwtf_Large: $006CE0FC;
    bwtf_Normal: $006CE0F8;
    bwtf_Mini: $006CE0F4;
    BoxColor: $006CF4AC; // where to store the color when using the box drawing function
    TextRectX: $006CE108; // what x to use when checking text rect
    TextRectY: $006CE0E0; // what y to use when checking text rect
    TextRectLeft: $006CE0D8; // the left value returned by GetTextRect
    TextRectTop: $006CE0DA; // the top value returned by GetTextRect
    TextRectRight: $006CE0DC; // the right value returned by GetTextRect
    TextRectBottom: $006CE0DE; // the bottom value returned by GetTextRect
    TextWidth: $006CE108; // the width of the text in the current font (GetTextWidth)
    SendActionPNum: $0051267C; // the player number in the SendAction function

    //functions
    BWFXN_CTextOut: $0048D1C0; // Centered TextOut
    BWFXN_TextOut: $0048D0C0; // TextOut
    BWFXN_DrawBox: $004E1D20; // Box drawing function
    BWFXN_DrawText: $004202B0; // Draw text at x,y
    BWFXN_FormatText: $0041FB30; // Format text with specified font
    BWFXN_RefreshText: $0041E0D0; // Refresh text in a portion of the screen
    BWFXN_GetTextRect: $004200D0; // Get the rect of the text in the current font
    BWFXN_GetTextWidth: $0041F920; // Get the width of the text in the current font
    BWFXN_SetSpeed: $004DEB90; // Set The Replay Speed
    BWFXN_PlaySound: $004BC270; // Play the specified sound

    // Hooks
    //HOOK_Draw: $0048CF79;
    HOOK_Draw: $0048CF6D;

    // Patches
    PTCH_TextRefresh1: $0047F26C;
    PTCH_TextRefresh2: $0047F120;
  );
*/

#ifdef V1161
	#define IN_REPLAY				0x006D0F14 // Byte -- Need to use this with InGame to determine
    #define IN_GAME					0x006D11EC // Byte
    #define IN_DEBRIEFING_ROOM		0x006D63C0 // Byte, = 1 if they're currently viewing the 'scores room' after the game
    #define MAP_FILE_PATH			0x0057FD3C // string
    #define SAVED_REP_NAME			0x0051BFB8 // string, contains name used in rep saving without '.rep'
    #define GAME_TIME				0x0057F23C // Dword
    #define REP_SPEED				0x006CDFD4 // byte, 6 for fastest
    #define REP_SPEED_MULTIPLIER	0x0050E058 // byte, x2 = 2, x4 = 4, etc.
    #define REP_SPEED_TIMING		0x005124F0 // byte, stores time for each frame, 42ms for fastest
    #define REP_PAUSED				0x006D11B0 // Byte
    #define GAME_PAUSED				0x006509C4 // Byte
    #define GAME_COMPLETE_DIALOG	0x00685178 // Byte, tells whether the "Exit Replay"/"Continue Playing" dlg is up
    #define GAME_DIGITAL_VOLUME		0x006CDFE4 // Byte, 0-100 for percent volume
    #define TICK_TIME_TABLE			0x005124D8 // Table of DWords giving actual timings for speeds <= Fastest (Dwords)
    #define REP_SELECTED_PLAYER		0x005153F8 // -1 if nothing is selected, otherwise player #
    #define PLAYER_NAMES			0x0057EEEB // 36 Bytes per player, first 24 are the string
    #define BUILDINGS_CONTROLLED	0x00581F34 // DW, +4*Player
    #define POPULATION				0x00581E14 // DW, +4*Player
    #define MINERALS				0x0057F0F0 //DW, +4*Player
    #define VESPENE					0x0057F120 //DW, +4*Player
    #define MY_PLAYER_NUM			0x00512684 // Current Player's number
    #define CURSOR_X				0x006CDDC4 // DW, X coord of the mouse cursor ingame
    #define CURSOR_Y				0x006CDDC8 // DW, Y coord of the mouse cursor ingame
    #define PLAYER_COLORS			0x00581DD6 // array of player colors
    #define CUR_TEXT_FORMAT			0x006D5DDC // DW, the current font the text is in
    #define BWTF_RESET				0x00000000
    #define BWTF_ULTRALARGE			0x006CE100
    #define BWTF_LARGE				0x006CE0FC
    #define BWTF_NORMAL				0x006CE0F8
    #define BWTF_MINI				0x006CE0F4
    #define BOX_COLOR				0x006CF4AC // where to store the color when using the box drawing function
    #define TEXT_RECT_X				0x006CE108 // what x to use when checking text rect
    #define TEXT_RECT_Y				0x006CE0E0 // what y to use when checking text rect
    #define TEXT_RECT_LEFT			0x006CE0D8 // the left value returned by GetTextRect
    #define TEXT_RECT_TOP			0x006CE0DA // the top value returned by GetTextRect
    #define TEXT_RECT_RIGHT			0x006CE0DC // the right value returned by GetTextRect
    #define TEXT_RECT_BOTTOM		0x006CE0DE // the bottom value returned by GetTextRect
    #define TEXT_WIDTH				0x006CE108 // the width of the text in the current font (GetTextWidth)
    #define SEND_ACTION_PNUM		0x0051267C // the player number in the SendAction function

    //functions
    #define BWFXN_CTEXTOUT			0x0048D1C0 // Centered TextOut
    #define BWFXN_TEXTOUT			0x0048D0C0 // TextOut
    #define BWFXN_DRAWBOX			0x004E1D20 // Box drawing function
    #define BWFXN_DRAWTEXT			0x004202B0 // Draw text at x,y
    #define BWFXN_FORMATTEXT		0x0041FB30 // Format text with specified font
    #define BWFXN_REFRESHTEXT		0x0041E0D0 // Refresh text in a portion of the screen
    #define BWFXN_GETTEXTRECT		0x004200D0 // Get the rect of the text in the current font
    #define BWFXN_GETTEXTWIDTH		0x0041F920 // Get the width of the text in the current font
    #define BWFXN_SETSPEED			0x004DEB90 // Set The Replay Speed
    #define BWFXN_PLAYSOUND			0x004BC270 // Play the specified sound

    // Hooks
    #define HOOK_DRAW				0x0048CF6D

    // Patches
    #define PTCH_TEXTREFRESH1		0x0047F26C
	#define PTCH_TEXTREFRESH2		0x0047F120
#endif

/*
procedure PeekMem(Address: Cardinal; Buffer: Pointer; Size: Cardinal);
procedure PokeMem(Address: Cardinal; Buffer: Pointer; Size: Cardinal);

function ReadMapPath: string;
function ReadSavedRepName: string;
function IsInReplay: Boolean;
function IsInGame: Boolean;
function IsPaused: Boolean;
function IsGameComplete: Boolean;
function IsFastestSpeed: Boolean;
function GetPNum: Integer;
function GetPlayerName(Player: Byte): string;
function IsObsMode: Boolean;
function GetBuildingsControlled(Player: Byte): Integer;
function GetPopulation(Player: Byte): Integer;
function GetMinerals(Player: Byte): Integer;
function GetVespene(Player: Byte): Integer;
function GetCurTextFormat: Cardinal;
function GetColoredPlayerName(Player:byte):String;
function FactionColor(Faction:byte):byte;
function FactionColorCode(Faction:byte):char;
*/

void PeekMem(DWORD address, void * buffer, DWORD size);
void PokeMem(DWORD address, void * buffer, DWORD size);

char * ReadMapPath();
char * ReadSavedRepName();
bool IsInReplay();
bool IsInGame();
bool IsPaused();
bool IsGameComplete();
int GetPNum();
char * GetPlayerName(byte player);
bool IsObsMode();
int GetBuildingsControlled(byte player);
int GetPopulation(byte player);
int GetMinerals(byte player);
int GetVespene(byte player);
DWORD GetCurTextFormat();
char * GetColoredPlayerName(byte player);
byte GetFactionColor(byte faction);
char GetFactionColorCode(byte faction);

#endif