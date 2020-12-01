#pragma once
#include "GameObject.h"
#define FLOATER_ANI_WALKING_RIGHT_UP	0
#define FLOATER_ANI_WALKING_LEFT_UP 1
#define FLOATER_ANI_WALKING_RIGHT_DOWN 2
#define FLOATER_ANI_WALKING_LEFT_DOWN 3
#define FLOATER_ANI_ATTACKING_RIGHT 4
#define FLOATER_ANI_ATTACKING_LEFT 5
#define FLOATER_WALKING_SPEED 0.05f;
#define	FLOATER_JUMPING_SPEED 0.035f;

#define FLOATER_BBOX_WIDTH 19
#define FLOATER_BBOX_HEIGHT 16
#define FLOATER_BBOX_HEIGHT_DIE 16

#define FLOATER_STATE_WALKING 100
#define FLOATER_STATE_DIE 200
#define FLOATER_STATE_FLYING 300
#include "Enemy.h"

class CFloaters : public Enemy
{
	bool isFolow;  //theo player 
	LPGAMEOBJECT target;
	bool isAttack;
public:
	CFloaters(float x, float y, LPGAMEOBJECT player);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void Attack();
	void flowPlayer(LPGAMEOBJECT player);
};

