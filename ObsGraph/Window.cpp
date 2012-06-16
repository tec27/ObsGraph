#include <stdio.h>
#include "Window.h"
#include "BWUtil.h"
#include "BWAddresses.h"
#include "BWColors.h"

int lastKey = 0;

Window::Window(char * szWinTitle, int sXPos, int sYPos, int sWidth, int sHeight, bool sVisible)
{
	//szTitle = _strdup(szWinTitle);
	xPos = sXPos;
	yPos = sYPos;
	width= sWidth;
	height = sHeight;
	visible = sVisible;
	bDragging = false;
	dragX = 0;
	dragY = 0;
	bgColor = 0;
	
	lblTitle = new Label(szWinTitle, 0, 0, width, BWTF_NORMAL, LBL_ALIGNCENTER, true, false, 41);
	testLabel1 = new Label("This is a really long label, motherfucker!", 1, 85, width-2);
	testLabel2 = new Label("This label is right aligned!", 1, 100, width-2, BWTF_MINI, LBL_ALIGNRIGHT);
}

Window::~Window(void)
{
	//free(szTitle);
	delete lblTitle;
	delete testLabel1;
	delete testLabel2;
}

void Window::draw(int parentX, int parentY)
{	
	if(!visible) return;
	
	unsigned char borderColor = RGBToBWColorByte(~BWColorByteToRGB(bgColor));
	
	int x = xPos + parentX;
	int y = yPos + parentY;
	
	char szXPos[24];
	char szYPos[24];
	char szDragX[24];
	char szDragY[24];
	char szLastKey[24];
	
	sprintf_s(szXPos, 24,  "X:     %d", xPos);
	sprintf_s(szYPos, 24,  "Y:     %d", yPos);
	sprintf_s(szDragX, 24, "DragX: %d", dragX);
	sprintf_s(szDragY, 24, "DragY: %d", dragY);
	sprintf_s(szLastKey, 24, "Last Key: %d", lastKey);

	BWDrawTransparentBox(x+1, y+1, width-2, height-2, bgColor);
		
	lblTitle->draw(x, y);
	testLabel1->draw(x, y);
	testLabel2->draw(x, y);		
	
	DWORD oldFormat = *(DWORD *)CUR_TEXT_FORMAT;
	BWFormatTextR(BWTF_NORMAL);
	//int textWidth = BWGetTextWidth(szTitle);
	//int centeredX = (width >> 1) - (textWidth >> 1) + xPos;
	//BWDrawText(centeredX,yPos+2, szTitle);
		
	BWDrawText(x + 4, y + 14, szXPos);
	BWDrawText(x + 4, y + 28, szYPos);
	BWDrawText(x + 4, y + 42, szDragX);
	BWDrawText(x + 4, y + 56, szDragY);
	BWDrawText(x + 4, y + 70, szLastKey);
	
	BWRestoreTextFormat(oldFormat);	
	
	BWDrawBox(x, y, width, 1, borderColor); // top border
	BWDrawBox(x, y+height-1, width, 1, borderColor); // bottom border
	BWDrawBox(x, y+1, 1, height-2, borderColor); // left border
	BWDrawBox(x+width-1, y+1, 1, height-2, borderColor); // right border	
}

void Window::receivedKey(int vkCode) 
{ 
	lastKey = vkCode;
}

void Window::receivedLeftClick(int x, int y)
{ 
}

void Window::receivedLeftDblClick(int x, int y)
{ 
	bgColor++;
}

void Window::receivedRightClick(int x, int y)
{ 
}

void Window::receivedRightDblClick(int x, int y)
{ 
	bgColor--;
}

void Window::receivedMiddleClick(int x, int y)
{ 
}

void Window::receivedMiddleDblClick(int x, int y)
{ 
}

void Window::startDrag(int x, int y)
{
	bDragging = true;
	dragX = x - xPos;
	dragY = y - yPos;
}

void Window::updateDrag(int x, int y)
{ 
	if(bDragging) {
		//FIXME: would be better to just clip drawing than to lock the window into these dimensions
		xPos = x - dragX;
		if(xPos < 0) { 
			dragX = x;
			xPos = 0;
		}
		if(xPos + width > 640) {
			xPos = 640 - width;
			dragX = x - xPos;
		}
		yPos = y - dragY;
		if(yPos < 0) {
			dragY = y;
			yPos = 0;
		}
		if(yPos + height > 480) {
			yPos = 480 - height;
			dragY = y - yPos;
		}
	}
}

void Window::endDrag(int x, int y)
{ 
	if(bDragging) {
		bDragging = false;
		xPos = x - dragX;
		if(xPos < 0) { 
			dragX = x;
			xPos = 0;
		}
		if(xPos + width > 640) {
			xPos = 640 - width;
			dragX = x - xPos;
		}
		yPos = y - dragY;
		if(yPos < 0) {
			dragY = y;
			yPos = 0;
		}
		if(yPos + height > 480) {
			yPos = 480 - height;
			dragY = y - yPos;
		}
	}
}

bool Window::hitTest(int x, int y)
{ 
	if(x >= xPos && y >= yPos) {
		if(x < xPos + width && y < yPos + height) {
			return true;
		} 
	}
	
	return false;
}
