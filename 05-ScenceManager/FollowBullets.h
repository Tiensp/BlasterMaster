#pragma once
#include "BulletObject.h"
#include "Enemy.h"
#include "Brick.h"
#include "FollowBullet.h"

class FollowBullets : public  BulletObject
{
	vector<BulletObject* > listFollowBullet;

public:
	FollowBullets(float _start_x, float _start_y, vector<LPGAMEOBJECT>* target);
	~FollowBullets();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
};

