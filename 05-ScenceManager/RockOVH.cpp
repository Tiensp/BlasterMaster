#include "RockOVH.h"

CRockOVH::CRockOVH(float X, float Y, int W, int H)
{
	this->x = X;
	this->y = Y;
	this->width = W;
	this->height = H;

	hp = 1;
}

void CRockOVH::Render()
{
	if (hp == 0)
	{
		return;
	}

	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CRockOVH::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (hp != 0)
	{
		l = x;
		t = y;
		r = x + 16;
		b = y + 16;
	}
	else return;
}