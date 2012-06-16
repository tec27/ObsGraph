#ifndef WINDOW_H
#define WINDOW_H

#include "Component.h"
#include "Label.h"

class Window : public Component
{
protected:
	//char * szTitle;
	int xPos, yPos;
	int width, height;
	bool visible;
	bool bDragging;
	int dragX, dragY;
	unsigned char bgColor; // this should probably be removed in favor of skinning
	//TODO: add in an icon image
	//TODO: add a component list
	Label * lblTitle;
	Label * testLabel1;
	Label * testLabel2;
public:
	Window(char * szWinTitle, int sXPos, int sYPos, int sWidth, int sHeight, bool visible = true);
	~Window(void);
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
