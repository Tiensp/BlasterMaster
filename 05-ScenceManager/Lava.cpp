#include "Lava.h"

CLava::CLava(float X, float Y, int W, int H)
{
	this->x = X;
	this->y = Y;
	this->width = W;
	this->height = H;
}

void CLava::Render()
{
	//animation_set->at(0)->Render(x, y);
	RenderBoundingBox(x,y);
}

void CLava::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}