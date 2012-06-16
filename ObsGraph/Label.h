#ifndef LABEL_H
#define LABEL_H

#include "Component.h"
#include "BWAddresses.h"
#include <windows.h>

#define LBL_ALIGNLEFT	0
#define LBL_ALIGNCENTER	1
#define LBL_ALIGNRIGHT	2

class Label : public Component
{
private:
	char * szText;
	int xPos, yPos;
	int width, height;
	DWORD font;
	unsigned char align;
	unsigned char bgColor;
	bool bgTransparent;
	bool visible;
public:
	Label(char * szLblText, int x, int y, int sWidth, DWORD sFont = BWTF_NORMAL, unsigned char sAlign = LBL_ALIGNLEFT, bool sVisible = true, bool sBgTransparent = true, unsigned char sBgColor = 0);
	~Label(void);
	void draw(int parentX, int parentY);
	void receivedKey(int vkCode);
	void receivedLeftClick(int x, int y);
	void receivedLeftDblClick(int x, int y);
	void receivedRightClick(int x, int y);
	void receivedRightDblClick(int x, int y);
	void receivedMiddleClick(int x, int y);
	void receivedMiddleDblClick(int x, int y);
	void startDrag(int x, int y);
	void updateDrag(int x, int y);
	void endDrag(int x, int y);
	bool hitTest(int x, int y);
};

#endif