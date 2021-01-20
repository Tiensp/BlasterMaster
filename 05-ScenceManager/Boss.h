#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "BulletBoss.h"
#include "BossHand.h"
#include "BossArm.h"
#define BOSS_ANI_WALKING_RIGHT_DOWN	0
#define BOSS_ANI_WALKING_RIGHT_UP 1
#define BOSS_ANI_WALKING_LEFT_DOWN 2
#define BOSS_ANI_WALKING_LEFT_UP 3

#define BOSS_BBOX_HEIGHT 66
#define BOSS_BBOX_WIDTH 60
#define BOSS_WALKING_SPEED 0.05f;
#define	BOSS_JUMPING_SPEED 0.035f;

class CBoss : public Enemy
{
protected:
	LPGAMEOBJECT target;
	BulletObject* boss_bullet;
	vector<CBossHand*> listBossHand;
	vector<CBossArm*> listBossArm;

	bool isAttack;

	int timeToAttack = 0;
public:
	CBoss(float x, float y, LPGAMEOBJECT player);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void Attack();

	void set_bullet_list();


};



