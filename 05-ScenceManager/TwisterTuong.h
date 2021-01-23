#pragma once
#include "GameObject.h"
#include "Enemy.h"


#define	TWISTERTUONG_ANI_WALKING_RIGHT 0
#define	TWISTERTUONG_ANI_WALKING_LEFT 1
#define	TWISTERTUONG_ANI_COLLISION_RIGHT 2
#define	TWISTERTUONG_ANI_COLLISION_LEFT 3
#define	TWISTERTUONG_ANI_DEATH 4

#define	TWISTERTUONG_SPEED_X 0.09f
#define	TWISTERTUONG_SPEED_Y 0.05f

#define TWISTERTUONG_BBOX_WIDTH 19
#define TWISTERTUONG_BBOX_HEIGHT 19

class CTWISTERTUONG : public Enemy
{
	bool isFollow;
	LPGAMEOBJECT target;

	bool isDoneDeath = false;

public:
	CTWISTERTUONG(float x, float y, LPGAMEOBJECT player);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void Attack();
	void flowPlayer(LPGAMEOBJECT player);
};
	
