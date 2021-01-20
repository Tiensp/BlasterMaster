#pragma once
#include "BulletObject.h"
#include "Brick.h"
#include "Sophia.h"
#include "BulletFloaters.h";

class BombBullet : public BulletObject
{
protected:

	int timeToSurvive;

	BulletFloaters* bullet1;
	BulletFloaters* bullet2;
	BulletFloaters* bullet3;

public:
	BombBullet() {};
	BombBullet(float _start_x, float _start_y);
	~BombBullet();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
};


