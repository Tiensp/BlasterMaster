#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "CannonBullet.h"
#define CANNON_ANI_SHOOT_RIGHT_LEFT 0
#define CANNON_ANI_SHOOT_TOP_BOTTOM 1
#define CANNON_ANI_DEATH 2


#define CANNON_BBOX_WIDTH 25
#define CANNON_BBOX_HEIGHT 25
#define CANNON_BBOX_HEIGHT_DIE 27

class CCannon : public Enemy
{
	LPGAMEOBJECT target;
	BulletObject* bullet1;
	BulletObject* bullet2;
	int timeChangeState = 400;
	int interval = 10;
	int timer;

	bool isDoneDeath;
public:
	CCannon(float x, float y, LPGAMEOBJECT player, int _typeItem);
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void Attack();
	


	void ChangeState();
	void flowPlayer(LPGAMEOBJECT player);
};




