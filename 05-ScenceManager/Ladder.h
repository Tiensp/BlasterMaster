#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

class CLadder : public CGameObject
{
protected:

public:
	CLadder(float X, float Y, int W, int H);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};