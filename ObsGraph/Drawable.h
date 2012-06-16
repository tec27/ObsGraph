#ifndef DRAWABLE_H
#define DRAWABLE_H

// Everything that can be drawn falls under Drawable (duh)

class Drawable abstract
{
public:
	virtual void draw(int parentX, int parentY) abstract; 
	//FIXME: fix parameters, maybe include an image buffer to draw to
};

#endif
