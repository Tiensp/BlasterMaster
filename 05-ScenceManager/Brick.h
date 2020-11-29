#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

class CBrick : public CGameObject
{
public: //Test
	int width;
	int height;
public:
	CBrick(float X, float Y, int W, int H);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};