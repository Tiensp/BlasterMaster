#pragma once
#include "BulletObject.h"
#include "Brick.h"
#include "Sophia.h"

class BulletShip : public CEnemyBullet
{

protected:
public:
	BulletShip(float _start_x, float y_start_y);
	~BulletShip();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};


