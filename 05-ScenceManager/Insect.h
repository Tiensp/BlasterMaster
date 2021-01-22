#pragma once
#include "GameObject.h"
#include "Enemy.h"

#define INSECT_ANI_DROP_DOWN 0
#define INSECT_ANI_WALKING_RIGHT_UP 1
#define INSECT_ANI_WALKING_RIGHT_DOWN 2
#define INSECT_ANI_WALKING_LEFT_UP 3
#define INSECT_ANI_WALKING_LEFT_DOWN 4
#define INSECT_ANI_DEATH 5

#define INSECT_WALKING_SPEED 0.025f;
#define	INSECT_JUMPING_SPEED 0.045f;

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
	int changeState;
	int interval = 10;
	int timer;

	bool isDoneDeath = false;
public:
	CInsect(float x, float y, LPGAMEOBJECT player, int _itemType);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void flowPlayer(LPGAMEOBJECT player);
};



