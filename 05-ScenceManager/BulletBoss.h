#pragma once
#include "BulletObject.h"
#include "Brick.h"
#include "Sophia.h"
#include "BulletFloaters.h";

class BossBullet : public CEnemyBullet
{
protected:

	int timeToSurvive;
public:
	BossBullet(float _start_x, float _start_y, int _nx);
	~BossBullet();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
	void CheckCollisionWithPlayer(vector<LPGAMEOBJECT>* coObjects);
};

