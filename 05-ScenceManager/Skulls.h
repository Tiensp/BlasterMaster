#pragma once
#include "GameObject.h"
#define SKULL_ANI_WALKING_RIGHT	0
#define SKULL_ANI_WALKING_LEFT 1
#define SKULL_ANI_ATTACKING_RIGHT 2
#define SKULL_ANI_ATTACKING_LEFT 3
#define SKULL_ANI_COLLISION_LEFT 6
#define SKULL_ANI_COLLISION_RIGHT 7

#define SKULL_WALKING_SPEED 0.09f;
#define	SKULL_JUMPING_SPEED 0.05f;

#define SKULL_BBOX_WIDTH 22
#define SKULL_BBOX_HEIGHT 19
#define SKULL_BBOX_HEIGHT_DIE 16

#define SKULL_STATE_DIE 100
#define SKULL_STATE_WALKING 200
#define SKULL_STATE_ATTACKING 300
#define SKULL_STATE_COLLISION 400

class CSkull : public CGameObject
{
	bool isFolow;  //theo player 
	LPGAMEOBJECT target;
	bool isAttack;
public:
	CSkull(float x, float y, LPGAMEOBJECT player);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void Attack();
	void flowPlayer(LPGAMEOBJECT player);
};



