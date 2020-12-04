#pragma once
#include "GameObject.h"
#include "Enemy.h"
#define CANNON_ANI_IDLE 0
#define CANNON_ANI_SHOOT_RIGHT_LEFT 1
#define CANNON_ANI_SHOOT_TOP_BOTTOM 2
#define CANNON_ANI_DEATH 3


#define CANNON_BBOX_WIDTH 27
#define CANNON_BBOX_HEIGHT 27
#define CANNON_BBOX_HEIGHT_DIE 27

class CCannon : public Enemy
{
	LPGAMEOBJECT target;

	int counter;

	bool isDeath;
	bool isDoneDeath;
	bool isShootTopBottom = true;
	bool isShootLeftRight;
public:
	CCannon(float x, float y, LPGAMEOBJECT player);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	void ChangeState();
	void flowPlayer(LPGAMEOBJECT player);
};




