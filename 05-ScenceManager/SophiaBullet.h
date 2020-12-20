#pragma once
#include "BulletObject.h"
#include "Enemy.h"
#include "Brick.h"

class SophiaBullet : public BulletObject
{
	int type = 0;
public:
	SophiaBullet() {};
	SophiaBullet(float _start_x, float _start_y);
	~SophiaBullet();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
	void Set_type(int _type) { type = _type; }

};
