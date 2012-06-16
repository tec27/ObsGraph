#include <windows.h>
#include "Label.h"
#include "BWAddresses.h"
#include "BWUtil.h"

Label::Label(char * szLblText, int x, int y, int sWidth, DWORD sFont, unsigned char sAlign, bool sVisible, bool sBgTransparent, unsigned char sBgColor)
{
	szText = _strdup(szLblText);
	xPos = x;
	yPos = y;
	width = sWidth;
	font = sFont;
	align = sAlign;
	visible = sVisible;
	bgTransparent = sBgTransparent;
	bgColor = sBgColor;
	
	switch(font) {
		case BWTF_MINI:			height = 11; break;
		case BWTF_NORMAL:		height = 13; break;
		case BWTF_LARGE:		height = 20; break;
		case BWTF_ULTRALARGE:	height = 20; break;
		default: height = 0;
	}
}

Label::~Label(void)
{
	free(szText);
}


void Label::draw(int parentX, int parentY)
{
	if(!visible) return;
	
	int x = xPos + parentX;
	int y = yPos + parentY;
	
	if(!bgTransparent)
		BWDrawBox(x, y, width, height, bgColor);
	
	DWORD oldFormat = *(DWORD *)CUR_TEXT_FORMAT;
	BWFormatTextR(font);
	
	char * renderStr = _strdup(szText);
	
	int textWidth = BWGetTextWidth(renderStr);
	if(textWidth > width) {
		while(textWidth > width) {
			int i = strlen(renderStr) - 1;
			renderStr[i--] = 0;

			for(int j = i; (i - j < 3) && (j >= 0); j--) {
				renderStr[j] = '.';
			}
			
			textWidth = BWGetTextWidth(renderStr);
		}
	}
	
	if(align == LBL_ALIGNLEFT) {
		BWDrawText(x, y, renderStr);
	}
	else if(align == LBL_ALIGNCENTER) {
		int centeredX = (width >> 1) - (textWidth >> 1) + x;
		BWDrawText(centeredX,y, renderStr);
	}
	else {
		int rightX = width - textWidth + x;
		BWDrawText(rightX, y, renderStr);
	}
	
	BWRestoreTextFormat(oldFormat);
}

void Label::receivedKey(int vkCode)
{
}

void Label::receivedLeftClick(int x, int y)
{
}

void Label::receivedLeftDblClick(int x, int y)
{
}

void Label::receivedRightClick(int x, int y)
{
}

void Label::receivedRightDblClick(int x, int y)
{
}

void Label::receivedMiddleClick(int x, int y)
{
}

void Label::receivedMiddleDblClick(int x, int y)
{
}

void Label::startDrag(int x, int y)
{
}

void Label::updateDrag(int x, int y)
{
}

void Label::endDrag(int x, int y)
{
}

bool Label::hitTest(int x, int y)
{
	if(x >= xPos && y >= yPos) {
		if(x < xPos + width && y < yPos + height) {
			return true;
		} 
	}
	
	return false;
}
