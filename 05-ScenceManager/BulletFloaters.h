#pragma once
#include "BulletObject.h"
#include "Enemy.h"
#include "Brick.h"

/*BULLET FLOATER*/
#define BULLET_FLOATER_ANI_WALKING_RIGHT_DOWN 0
#define BULLET_FLOATER_ANI_WALKING_LEFT_DOWN 1
#define BULLET_FLOATER_ANI_COLLISON 2

#define BULLET_FLOATER_SPEED 0.2f;

class BulletFloaters : public BulletObject
{

public:
	BulletFloaters() {};
	BulletFloaters(float x, float y);
	~BulletFloaters();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) ;
};

