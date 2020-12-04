#pragma once
#include "GameObject.h"
#define FLOATER_ANI_WALKING_RIGHT_UP	0
#define FLOATER_ANI_WALKING_LEFT_UP 1
#define FLOATER_ANI_WALKING_RIGHT_DOWN 2
#define FLOATER_ANI_WALKING_LEFT_DOWN 3
#define FLOATER_ANI_ATTACKING_RIGHT_UP 4
#define FLOATER_ANI_ATTACKING_RIGHT_DOWN 5
#define FLOATER_ANI_ATTACKING_LEFT_UP 6 
#define FLOATER_ANI_ATTACKING_LEFT_DOWN 7 
#define FLOATER_ANI_DEATH 8 
#define FLOATER_WALKING_SPEED 0.05f;
#define	FLOATER_JUMPING_SPEED 0.035f;

#define FLOATER_BBOX_WIDTH 19
#define FLOATER_BBOX_HEIGHT 16
#define FLOATER_BBOX_HEIGHT_DIE 16

#define FLOATER_STATE_WALKING 100
#define FLOATER_STATE_DIE 200
#define FLOATER_STATE_FLYING 300
#include "Enemy.h"
#include "BulletFloaters.h"

class CFloaters : public Enemy
{
protected:
	LPGAMEOBJECT target;
	bool isAttack;
	vector<BulletObject* > p_bullet_list;

	bool isDoneDeath;
	bool isDeath;
public:
	CFloaters(float x, float y, LPGAMEOBJECT player);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void Attack();
	void flowPlayer(LPGAMEOBJECT player);
	//BulletFloaters* Get_bullet_floater() { return bulletFloaters; }
	vector<BulletObject*> Get_Bullet_List() { return p_bullet_list; }

};


