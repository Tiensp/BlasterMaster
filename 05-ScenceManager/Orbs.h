#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "GameDefine.h"

#define ORB_ANI_WALKING_RIGHT 0
#define ORB_ANI_WALKING_LEFT 1
#define ORB_ANI_WALKING_RIGHT_UP 2
#define ORB_ANI_WALKING_RIGHT_DOWN	3
#define ORB_ANI_WALKING_LEFT_UP 4
#define ORB_ANI_WALKING_LEFT_DOWN 5
#define ORB_ANI_DEATH 6

#define LAST_FRAME 2

#define ORB_WALKING_SPEED 0.0350f;
#define	ORB_JUMPING_SPEED 0.0275f;

#define ORB_BBOX_WIDTH 20
#define ORB_BBOX_HEIGHT 19
#define ORB_BBOX_HEIGHT_DIE 16

#define ORB_STATE_DIE 100
#define ORB_STATE_WALKING 200
#define ORB_STATE_ATTACKING 300
#define ORB_STATE_COLLISION 400

class COrb : public Enemy
{
	bool isFolow;  //theo player 
	LPGAMEOBJECT target;
	bool isAttack = false;
	bool isDoneDeath = false;
	//bool isDeath = false;
public:
	COrb(float x, float y, LPGAMEOBJECT player, int _typeItem);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void Attack();
	void flowPlayer(LPGAMEOBJECT player);
};




