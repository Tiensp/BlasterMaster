#pragma once
#include "BulletObject.h"
#include "Brick.h"
#include "Sophia.h"
#include "EnemyBullet.h"

class BulletSkull : public CEnemyBullet
{

protected:

	LPGAMEOBJECT target;

	bool isDrop; 
	bool isJump;

	int timer;
	int interval = 20;
	int timeToExplosive = 2000;
public:

	BulletSkull(float _start_x, float y_start_y, LPGAMEOBJECT player);
	~BulletSkull();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	virtual void SetState(int state);
};

