#pragma once
#include "BulletObject.h"
#include "Enemy.h"
#include "Brick.h"

class FollowBullet : public BulletObject
{
	int type = 0;
	CGameObject* target;
public:
	FollowBullet(float _start_x, float _start_y, CGameObject* _target );
	~FollowBullet();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
	void Set_type(int _type) { type = _type; }
};
