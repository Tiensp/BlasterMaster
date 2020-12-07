#pragma once
#include "GameObject.h"
#include "Enemy.h"
#define CANNON_ANI_SHOOT_RIGHT_LEFT 0
#define CANNON_ANI_SHOOT_TOP_BOTTOM 1
#define CANNON_ANI_DEATH 2


#define CANNON_BBOX_WIDTH 25
#define CANNON_BBOX_HEIGHT 25
#define CANNON_BBOX_HEIGHT_DIE 27

class CCannon : public Enemy
{
	LPGAMEOBJECT target;

	int timeChangeState = 400;
	int interval = 10;
	int timer;

	bool isDeath;
	bool isDoneDeath;
public:
	CCannon(float x, float y, LPGAMEOBJECT player);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	void ChangeState();
	void flowPlayer(LPGAMEOBJECT player);
};




