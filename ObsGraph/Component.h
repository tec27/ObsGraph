#ifndef COMPONENT_H
#define COMPONENT_H

#include "Drawable.h"

// Components are drawable items that can interact with the mouse/keyboard and receive focus

class Component abstract : public Drawable
{
public:
	virtual void receivedKey(int vkCode) abstract;
	virtual void receivedLeftClick(int x, int y) abstract;
	virtual void receivedLeftDblClick(int x, int y) abstract;
	virtual void receivedRightClick(int x, int y) abstract;
	virtual void receivedRightDblClick(int x, int y) abstract;
	virtual void receivedMiddleClick(int x, int y) abstract;
	virtual void receivedMiddleDblClick(int x, int y) abstract;
	// TODO: check out other mouse button stuff
	virtual void startDrag(int x, int y) abstract;
	virtual void updateDrag(int x, int y) abstract;
	virtual void endDrag(int x, int y) abstract;
	virtual bool hitTest(int x, int y) abstract;
};

#endif