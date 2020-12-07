#pragma once
#include "BulletObject.h"
#include "SophiaBullet.h"
class ThunderBullet : public BulletObject
{

public:
	/*ThreeBullet() {};*/
	ThunderBullet(float _start_x, float _start_y);
	~ThunderBullet() {};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
};

