#pragma once
#include "GameObject.h"
#include "BulletObject.h"

class CEnemyBullet : public BulletObject
{
public:
	~CEnemyBullet();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) ;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	virtual void Render() {};
	void CheckCollisionWithPlayer(vector<LPGAMEOBJECT>* coObjects);
};

