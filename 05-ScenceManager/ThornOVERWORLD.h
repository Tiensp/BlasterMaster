#pragma once
#include "GameObject.h"

class CThornOVW : public CGameObject
{
protected:

public:
	CThornOVW(float X, float Y, int W, int H);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};
