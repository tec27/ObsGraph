#ifndef BWUTIL_H
#define BWUTIL_H

#include <windows.h>

/*
procedure BWCenteredTextOut(Text: PChar); stdcall; overload;
procedure BWTextOut(Text: PChar); stdcall; overload;
procedure BWDrawBox(x,y,w,h: DWORD; clr: BYTE); stdcall;
procedure BWDrawTransparentBox(x,y,w,h: DWORD; midclr: BYTE); stdcall;
procedure BWDrawPixel(x,y: DWORD; clr: Byte); stdcall;
procedure BWDrawText(x, y: DWORD; str: PChar); stdcall;
procedure BWPlaySound(Sound: DWORD); stdcall;
procedure BWRestoreTextFormat(StoredFormat: DWORD); stdcall;
procedure BWFormatText(format: DWORD); stdcall;
procedure BWFormatTextR(format: DWORD); stdcall;
procedure BWDrawFormattedText(x, y: DWORD; str: PChar; format: DWORD); stdcall;
procedure BWRefreshText(x, y, x2, y2: DWORD); stdcall;
function BWGetTextRect(x, y: DWORD; str: PChar): TRect; stdcall;
function BWGetTextWidth(str: PChar): Integer; stdcall;
*/

void BWCenteredTextOut(char * text);
void BWTextOut(char * text);
void BWDrawBox(DWORD x, DWORD y, DWORD w, DWORD h, byte clr);
void BWDrawTransparentBox(unsigned int x, unsigned int y, unsigned int w, unsigned int h, byte midclr);
void BWDrawPixel(DWORD x, DWORD y, byte clr);
void BWDrawText(DWORD x, DWORD y, char * text);
void BWPlaySound(DWORD sound);
void BWRestoreTextFormat(DWORD storedFormat);
void BWFormatText(DWORD format);
void BWFormatTextR(DWORD format);
void BWDrawFormattedText(DWORD x, DWORD y, char * text, DWORD format);
void BWRefreshText(DWORD x, DWORD y, DWORD x2, DWORD y2);
// RECT BWGetTextRect(DWORD x, DWORD y, char * str);
int BWGetTextWidth(char * text);

#endif