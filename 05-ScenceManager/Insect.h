#pragma once
#include "GameObject.h"
#include "Enemy.h"
#define INSECT_ANI_WALKING_RIGHT_UP 0
#define INSECT_ANI_WALKING_RIGHT_DOWN 1
#define INSECT_ANI_WALKING_LEFT_UP 2
#define INSECT_ANI_WALKING_LEFT_DOWN 3

#define INSECT_WALKING_SPEED 0.0375f;
#define	INSECT_JUMPING_SPEED 0.035f;

#define INSECT_BBOX_WIDTH 19
#define INSECT_BBOX_HEIGHT 19
#define INSECT_BBOX_HEIGHT_DIE 16

#define INSECT_STATE_DIE 100
#define INSECT_STATE_WALKING 200
#define INSECT_STATE_ATTACKING 300
#define INSECT_STATE_COLLISION 400

class CInsect : public Enemy
{
	bool isFolow;  //theo player 
	LPGAMEOBJECT target;
	int timeChangeState = 1500;
	int interval = 30;
	int timer;
public:
	CInsect(float x, float y, LPGAMEOBJECT player);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void flowPlayer(LPGAMEOBJECT player);
};



