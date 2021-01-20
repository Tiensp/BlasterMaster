#pragma once
#include "BulletObject.h"
#include "Brick.h"
#include "Sophia.h"
#include "BulletFloaters.h";

class BossBullet : public BulletObject
{
protected:

	int timeToSurvive;

	BulletFloaters* bullet1;
	BulletFloaters* bullet2;
	BulletFloaters* bullet3;
	BulletFloaters* bullet4;

public:
	BossBullet() {};
	BossBullet(float _start_x, float _start_y, int _nx);
	~BossBullet();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
};

