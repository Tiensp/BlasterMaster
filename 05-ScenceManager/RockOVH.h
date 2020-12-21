#pragma once
#include "GameObject.h"

class CRockOVH : public CGameObject
{
protected:

public:
	CRockOVH(float X, float Y, int W, int H);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};