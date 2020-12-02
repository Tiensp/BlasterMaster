#pragma once
#include "GameObject.h"
#include "Enemy.h"
#define WORM_ANI_WALKING_LEFT	1
#define WORM_ANI_WALKING_RIGHT	0
#define WORM_ANI_DEAD 2

#define WORM_WALKING_SPEED 0.03f;
#define	WORM_JUMPING_SPEED 0.163f;

#define WORM_BBOX_WIDTH 20
#define WORM_BBOX_HEIGHT 10
#define WORM_BBOX_HEIGHT_DIE 16

#define WORM_STATE_WALKING 100
#define WORM_STATE_DIE 200

class CWorm : public Enemy
{
	bool isFolow;  //theo player 




public:
	CWorm(float x, float y, LPGAMEOBJECT player);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void flowPlayer(LPGAMEOBJECT player);
};

