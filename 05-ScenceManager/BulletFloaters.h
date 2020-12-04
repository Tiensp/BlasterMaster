#pragma once
#include "BulletObject.h"
#include "Brick.h"

#define BULLET_FLOATERS_ANI 15001

#define BULLET_FLOATER_ANI_WALKING_RIGHT_DOWN 0
#define BULLET_FLOATER_ANI_WALKING_LEFT_DOWN 1
#define BULLET_FLOATER_ANI_COLLISON 2
class BulletFloaters : public BulletObject
{
public:
	BulletFloaters(float _start_x, float y_start_y);
	~BulletFloaters();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) ;
};

