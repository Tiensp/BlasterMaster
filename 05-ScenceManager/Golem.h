#pragma once
#include "Enemy.h"
#define GOLEM_ANI_WALKING_LEFT	1
#define GOLEM_ANI_WALKING_RIGHT	0
#define GOLEM_WALKING_SPEED 0.03f;

#define GOLEM_BBOX_WIDTH 16
#define GOLEM_BBOX_HEIGHT 26
#define GOLEM_BBOX_HEIGHT_DIE 16

#define GOLEM_STATE_WALKING 100
#define GOLEM_STATE_DIE 200

class CGolem : public CGameObject
{

	
public:
	CGolem();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};

