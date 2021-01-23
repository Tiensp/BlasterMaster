#pragma once
#include "BulletObject.h"
#include "EnemyBullet.h"
class CCannonBullet : public CEnemyBullet
{
public:
	CCannonBullet(float _start_x, float _start_y);
	~CCannonBullet();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
};

