#include <windows.h>
#include "BWUtil.h"
#include "BWAddresses.h"

/*
procedure BWCenteredTextOut(Text: PChar); stdcall;
asm
  pushad
	mov esi, [Text]
  mov eax, -1
  push 0h
  push esi
	call dword ptr [Offsets.BWFXN_CTextOut]
	popad
end;
*/
void BWCenteredTextOut(char * text)
{
	__asm {
		pushad
		mov esi, [text]
		mov eax, -1
		push 0h
		push esi
		mov esi, BWFXN_CTEXTOUT
		call esi
		popad
	}
}

/*
procedure BWTextOut(Text: PChar); stdcall;
asm
  pushad
  xor eax,eax
  mov edi,Text
  call dword ptr [Offsets.BWFXN_TextOut]
  popad
end;
*/
void BWTextOut(char * text)
{
	__asm {
		pushad
		xor eax, eax
		mov edi, text
		mov esi, BWFXN_TEXTOUT
		call esi
		popad
	}
}

/*
procedure BWDrawBox(x,y,w,h: DWORD; clr: BYTE); stdcall;
// Thanks Perma
asm
  pushad
  mov cl,clr
  mov eax,[Offsets.BoxColor]
  mov byte ptr ds:[eax], cl
  push h
  push w
  push y
  push x
  call dword ptr [Offsets.BWFXN_DrawBox]
  popad
end;
*/
void BWDrawBox(DWORD x, DWORD y, DWORD w, DWORD h, byte clr)
{
	__asm {
		pushad
		mov cl, clr
		mov eax, BOX_COLOR
		mov byte ptr ds:[eax], cl
		push h
		push w
		push y
		push x
		mov esi, BWFXN_DRAWBOX
		call esi
		popad
	}
}

/*
procedure BWDrawTransparentBox(x,y,w,h: DWORD; midclr: BYTE); stdcall;
// Thanks Zephyrix
var
  I,Z: Integer;
  bDraw: Boolean;
begin
  bDraw := True;
  for I := y to y+h-1 do    // Iterate to draw innards
  begin
    for Z := x to x+w-1 do    // Iterate
    begin
      if bDraw then
        BWDrawBox(Z,I,1,1,midclr);
      bDraw := not bDraw;
    end;    // for
    if w mod 2 = 0  then
      bDraw := not bDraw;
  end;    // for
end;
*/
void BWDrawTransparentBox(unsigned int x, unsigned int y, unsigned int w, unsigned int h, byte midclr)
{
	bool bDraw = true;
	for(unsigned int i = y; i < y+h; i++) {
		for(unsigned int z = x; z < x+w; z++) {
			if(bDraw)
				BWDrawBox(z,i,1,1,midclr);
			bDraw = !bDraw;
		}
		if(w % 2 == 0)
			bDraw = !bDraw;
	}
}

/*
procedure BWDrawPixel(x,y: DWORD; clr: Byte); stdcall;
asm
  pushad
  mov cl, clr
  mov eax,[Offsets.BoxColor]
  mov byte ptr ds:[eax], cl
  push 1
  push 1
  push y
  push x
  call dword ptr [Offsets.BWFXN_DrawBox]
  popad
end;
*/
void BWDrawPixel(DWORD x, DWORD y, byte clr)
{
	__asm {
		pushad
		mov cl, clr
		mov eax, BOX_COLOR
		mov byte ptr ds:[eax], cl
		push 1
		push 1
		push y
		push x
		mov esi, BWFXN_DRAWBOX
		call esi
		popad
	}
}

/*
procedure BWDrawText(x, y: DWORD; str: PChar); stdcall;
asm
  pushad
  mov eax, [str]
  mov esi, x
  push y
  call dword ptr [Offsets.BWFXN_DrawText]
  popad
end;
*/
void BWDrawText(DWORD x, DWORD y, char * text)
{
	__asm {
		pushad
		mov eax, [text]
		mov esi, x
		push y
		mov ecx, BWFXN_DRAWTEXT
		call ecx
		popad
	}
}

/*
procedure BWPlaySound(Sound: DWORD); stdcall;  // 0 - 0x477 allowed as values
asm
  pushad
  push 0
  push 0
  push 20
  push Sound
  call dword ptr [Offsets.BWFXN_PlaySound]
  popad
end;
*/
void BWPlaySound(DWORD sound)
{
	__asm {
		pushad
		push 0
		push 0
		push 20
		push sound
		mov eax, BWFXN_PLAYSOUND
		call eax
		popad
	}
}

/*
procedure BWRestoreTextFormat(StoredFormat: DWORD); stdcall;
asm
  pushad
  mov ecx, StoredFormat
  call dword ptr [Offsets.BWFXN_FormatText]
  popad
end;
*/
void BWRestoreTextFormat(DWORD storedFormat)
{
	__asm {
		pushad
		mov ecx, storedFormat
		mov eax, BWFXN_FORMATTEXT
		call eax
		popad
	}
}

/*
procedure BWFormatText(format: DWORD); stdcall;
asm
  pushad
  cmp format, 0
  jnz @PtrLoad
  xor ecx, ecx
  jmp @FuncCall
@PtrLoad:
  mov eax, DWORD PTR SS: [format]
  mov ecx, DWORD PTR DS: [eax]
@FuncCall:
  call dword ptr [Offsets.BWFXN_FormatText]
  popad
end;
*/
void BWFormatText(DWORD format)
{
	__asm {
		pushad
		cmp format, 0
		jnz PtrLoad
		xor ecx, ecx
		jmp FuncCall
	PtrLoad:
		mov eax, dword ptr ss: [format]
		mov ecx, dword ptr ds: [eax]
	FuncCall:
		mov edx, BWFXN_FORMATTEXT
		call edx
		popad
	}
}

/*
procedure BWFormatTextR(format: DWORD); stdcall; // calls Reset first so we can change the font properly
begin
  BWFormatText(Offsets.bwtf_Reset);
  BWFormatText(format);
end;
*/
void BWFormatTextR(DWORD format)
{
	BWFormatText(BWTF_RESET);
	BWFormatText(format);
}

/*
procedure BWDrawFormattedText(x, y: DWORD; str: PChar; format: DWORD); stdcall;
begin
  BWFormatTextR(format);
  BWDrawText(x, y, str);
end;
*/
void BWDrawFormattedText(DWORD x, DWORD y, char * text, DWORD format)
{
	BWFormatTextR(format);
	BWDrawText(x, y, text);
}

/*
procedure BWRefreshText(x, y, x2, y2: DWORD); stdcall;
asm
  pushad
  push x2
  mov eax, x
  mov ecx, y
  mov edx, y2
  call dword ptr [Offsets.BWFXN_RefreshText];
  popad
end;
*/
void BWRefreshText(DWORD x, DWORD y, DWORD x2, DWORD y2) 
{
	__asm {
		pushad
		push x2
		mov eax, x
		mov ecx, y
		mov edx, y2
		mov esi, BWFXN_REFRESHTEXT
		call esi
		popad
	}
}

/*
// NOTE: This will oddly actually draw the string, which is not what we want
function BWGetTextRect(x, y: DWORD; str: PChar): TRect; stdcall;
begin
  asm
    pushad
    push ecx
    lea ecx,[esp]
    push ecx
    mov eax, [Offsets.TextRectX]
    mov edi, x
    mov dword ptr [eax],edi
    mov eax, [Offsets.TextRectY]
    mov edi, y
    mov dword ptr [eax],edi
    mov eax,[str]
    call dword ptr [Offsets.BWFXN_GetTextRect]
    pop ecx
    popad
  end;
  Result.Left := (Integer(Word(Pointer(Offsets.TextRectLeft)^)));
  Result.Top := (Integer(Word(Pointer(Offsets.TextRectTop)^)));
  Result.Right := (Integer(Word(Pointer(Offsets.TextRectRight)^)));
  Result.Bottom := (Integer(Word(Pointer(Offsets.TextRectBottom)^)));
end;
*/
// not gonna implement this, not used ever

/*
function BWGetTextWidth(str: PChar): Integer; stdcall;
begin
  asm
    pushad
    mov ecx, [Offsets.TextWidth]
    mov dword ptr ds:[ecx],0
    mov eax, [str]
    call dword ptr [Offsets.BWFXN_GetTextWidth]
    popad
  end;
  Result := (PInteger(Offsets.TextWidth))^;
end;
*/
int BWGetTextWidth(char * text)
{
	__asm {
		pushad
		mov ecx, TEXT_WIDTH
		mov dword ptr ds:[ecx], 0
		mov eax, [text]
		mov edx, BWFXN_GETTEXTWIDTH
		call edx
		popad
	}
	
	return *(int *)(TEXT_WIDTH);
}
