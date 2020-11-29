#pragma once
#include "GameObject.h"
#include "Enemy.h"
#define GOLEM_ANI_WALKING_LEFT	1
#define GOLEM_ANI_WALKING_RIGHT	0
#define GOLEM_WALKING_SPEED 0.03f;
#define	GOLEM_JUMPING_SPEED 0.163f;

#define GOLEM_BBOX_WIDTH 16
#define GOLEM_BBOX_HEIGHT 26
#define GOLEM_BBOX_HEIGHT_DIE 16

#define GOLEM_STATE_WALKING 100
#define GOLEM_STATE_DIE 200
#define GOLEM_STATE_JUMPING 300

class CGolem : public Enemy
{
	bool isFolow;  //theo player 




public:
	CGolem(float x, float y, LPGAMEOBJECT player);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void flowPlayer(LPGAMEOBJECT player);
};

