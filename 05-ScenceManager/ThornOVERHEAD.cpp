#include "ThornOVERHEAD.h"

CThornOVH::CThornOVH(float X, float Y, int W, int H)
{
	this->x = X;
	this->y = Y;
	this->width = W;
	this->height = H;
}

void CThornOVH::Render()
{
	//animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CThornOVH::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}