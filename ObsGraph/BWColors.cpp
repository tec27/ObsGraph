#include <windows.h>
#include <math.h>
#include "BWColors.h"
/*
function RGBToBWColorByte(RGB: Dword): Byte;
var
  MinDist, NewDist: Extended;
  MinSpot: Integer;
  R, G, B, R2, G2, B2: Byte;
  I: Integer;
begin
  R := GetRValue(RGB);
  G := GetGValue(RGB);
  B := GetBValue(RGB);
  R2 := GetRValue(BWColorsRGB[0]);
  G2 := GetGValue(BWColorsRGB[0]);
  B2 := GetBValue(BWColorsRGB[0]);
  MinDist := Sqrt(Sqr(R - R2) + Sqr(G - G2) + Sqr(B - B2));
  MinSpot := 0;
  for I := 1 to High(BWColorsRGB) do
  begin
    R2 := GetRValue(BWColorsRGB[I]);
    G2 := GetGValue(BWColorsRGB[I]);
    B2 := GetBValue(BWColorsRGB[I]);
    NewDist := Sqrt(Sqr(R - R2) + Sqr(G - G2) + Sqr(B - B2));
    if NewDist < MinDist then
    begin
      MinDist := NewDist;
      MinSpot := I;
    end;
  end;

  Result := BWColorsByte[MinSpot];
end;
*/
byte RGBToBWColorByte(DWORD rgb)
{
	byte R = GetRValue(rgb);
	byte G = GetGValue(rgb);
	byte B = GetBValue(rgb);
	byte R2 = GetRValue(BWColorsRGB[0]);
	byte G2 = GetGValue(BWColorsRGB[0]);
	byte B2 = GetBValue(BWColorsRGB[0]);
	double MinDist = sqrt(pow((double)(R - R2),2) + pow((double)(G - G2),2) + pow((double)(B - B2),2));
	int MinSpot = 0;
	if(MinDist == 0) return BWColorsByte[MinSpot];
	
	for(int i = 0; i < 188; i++) {
		R2 = GetRValue(BWColorsRGB[i]);
		G2 = GetGValue(BWColorsRGB[i]);
		B2 = GetBValue(BWColorsRGB[i]);
		double NewDist = sqrt(pow((double)(R - R2),2) + pow((double)(G - G2),2) + pow((double)(B - B2),2));
		if (NewDist < MinDist) {
			MinDist = NewDist;
			MinSpot = i;
		}
		
		if(MinDist == 0) return BWColorsByte[MinSpot];
	}
	
	return BWColorsByte[MinSpot];
}

/*
function BWColorByteToRGB(dByte: Dword): Dword;
var
  I: Integer;
begin
  for I := Low(BWColorsByte) to High(BWColorsByte) do
  begin
    if BWColorsByte[I] = dByte then
    begin
      Result := BWColorsRGB[I];
      exit;
    end;
  end;
  Result := $0;
end;
*/
DWORD BWColorByteToRGB(DWORD dByte)
{
	for(int i = 0; i < 188; i++) {
		if(BWColorsByte[i] == dByte)
			return BWColorsRGB[i];
	}
	
	return 0;
}