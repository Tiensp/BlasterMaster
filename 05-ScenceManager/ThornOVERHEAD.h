#pragma once
#include "GameObject.h"

class CThornOVH : public CGameObject
{
protected:

public:
	CThornOVH(float X, float Y, int W, int H);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};
