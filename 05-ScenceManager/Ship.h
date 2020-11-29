#pragma once
#include "GameObject.h"
#include "Enemy.h"

#define SHIP_ANI_WALKING_RIGHT	0
#define SHIP_ANI_WALKING_LEFT 1
#define SHIP_ANI_ATTACKING_RIGHT 2
#define SHIP_ANI_ATTACKING_LEFT 3

#define SHIP_WALKING_SPEED 0.09f;
#define	SHIP_JUMPING_SPEED 0.05f;

#define SHIP_BBOX_WIDTH 22
#define SHIP_BBOX_HEIGHT 19
#define SHIP_BBOX_HEIGHT_DIE 16

#define SHIP_STATE_DIE 100
#define SHIP_STATE_WALKING 200
#define SHIP_STATE_ATTACKING 300
#define SHIP_STATE_COLLISION 400

class CShip : public Enemy
{
	bool isFolow;  //theo player 
	LPGAMEOBJECT target;
	bool isAttack;
public:
	CShip(float x, float y, LPGAMEOBJECT player);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void Attack();
	void flowPlayer(LPGAMEOBJECT player);
};




