#pragma once
#include "BulletObject.h"
#include "Enemy.h"
#include "Brick.h"

class BigJasonBullet : public BulletObject
{

public:
	BigJasonBullet(float _start_x, float _start_y);
	~BigJasonBullet();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
};
