#pragma once
#include "GameObject.h"

class CLava : public CGameObject
{
protected:

public:
	CLava(float X, float Y, int W, int H);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};