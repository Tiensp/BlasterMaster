#pragma once
#include "GameObject.h"
#include "Enemy.h"
#define EYEBALL_ANI_WALKING 0
#define EYEBALL_ANI_IDLE 1
#define EYEBALL_ANI_DEATH 2

#define EYEBALL_WALKING_SPEED_X 0.015f;
#define	EYEBALL_WALKING_SPEED_Y 0.0095f;

#define EYEBALL_BBOX_WIDTH 17
#define EYEBALL_BBOX_HEIGHT 17
#define EYEBALL_BBOX_HEIGHT_DIE 16

class CEyeballs : public Enemy
{
	LPGAMEOBJECT target;

	int counter;
	int timeChangeState = 5000;
	int interval = 20;
	int timer;

	bool isDeath;
	bool isDoneDeath;
public:
	CEyeballs(float x, float y, LPGAMEOBJECT player);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();


	int RandomNXNY(int a, int b);
	void Move();
	void flowPlayer(LPGAMEOBJECT player);
};



