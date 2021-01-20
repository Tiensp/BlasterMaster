#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "BulletBomb.h"
#include "BulletShip.h"

#define BOMB_ANI_IDLE	0
#define BOMB_ANI_DEAD	1

#define BOMB_BBOX_WIDTH 4
#define BOMB_BBOX_HEIGHT 4
#define BOMB_BBOX_HEIGHT_DIE 4

class CBomb : public Enemy
{
	BulletObject* bomb_bullet;

	int changeState;
	bool isDoneDeath = false;
public:
	CBomb(float x, float y);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};





