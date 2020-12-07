#pragma once
#include "BulletObject.h"
#include "Enemy.h"
#include "Brick.h"

class JasonBullet : public BulletObject
{
	int type = 0;
public:
	JasonBullet(float _start_x, float _start_y);
	~JasonBullet();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
	void Set_type(int _type) { type = _type; }
};
