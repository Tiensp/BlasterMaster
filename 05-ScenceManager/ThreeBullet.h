#pragma once
#include "BulletObject.h"
#include "SophiaBullet.h"
class ThreeBullet : public BulletObject
{
	SophiaBullet* bullet1;
	SophiaBullet* bullet2;
	SophiaBullet* bullet3;
public:
	/*ThreeBullet() {};*/
	ThreeBullet(float _start_x, float _start_y, int _nx);
	~ThreeBullet() {};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
	void Render() ;
};

