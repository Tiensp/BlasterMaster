#pragma once
#include "BulletObject.h"
#include "Brick.h"
#include "Sophia.h"

class BulletEyeball : public CEnemyBullet
{

protected:
	CSophia* sophia;

	int followPlayer = 1;

	LPGAMEOBJECT target;
public:
	BulletEyeball(float _start_x, float y_start_y, LPGAMEOBJECT player);
	~BulletEyeball();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetState(int state);
};


