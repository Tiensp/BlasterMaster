#pragma once
#include "GameObject.h"
#include "State.h"
#include "GameDefine.h"
#include "BigJasonBullet.h"
#include "EnemyBullet.h"


#define BIG_JASON_WALKING_SPEED		0.09f 
//0.1f
#define BIG_JASON_JUMP_SPEED_Y		0.5f
#define BIG_JASON_JUMP_DEFLECT_SPEED 0.2f

#define BIG_JASON_DIE_DEFLECT_SPEED	 0.5f

#define BIG_JASON_STATE_IDLE					100
#define BIG_JASON_STATE_WALKING_RIGHT			101
#define BIG_JASON_STATE_WALKING_LEFT			103
#define BIG_JASON_STATE_JUMP					104
#define BIG_JASON_STATE_GUN_UP					105
#define BIG_JASON_STATE_IDLE_GUN_UP				106
#define BIG_JASON_STATE_GUN_DOWN				107
#define BIG_JASON_STATE_TURN					108
#define BIG_JASON_STATE_DIE					130



#define BIG_JASON_ANI_DIE				1

#define	BIG_JASON_LEVEL_SMALL	1
#define	BIG_JASON_LEVEL_BIG		2

#define BIG_JASON_SMALL_BBOX_WIDTH  20
#define BIG_JASON_SMALL_BBOX_HEIGHT 31

#define BIG_JASON_BIG_BBOX_WIDTH  24
#define BIG_JASON_BIG_BBOX_HEIGHT 32

#define BIG_JASON_UNTOUCHABLE_TIME 800


class CBigJason : public CGameObject
{
protected:
	static CBigJason* __instance;
	int level;
	int untouchable;
	DWORD untouchable_start;
	DWORD lifeTimeAni;

	bool isAutoGo = false;
	float autoGoDes;
	bool isDead;
	float start_x;			// initial position of BigJason at scene
	float start_y;
	int energy=5;
	int health = 4;	// Máu nhân vật
	vector<BulletObject*> p_bullet_list;
	bool isInjured;
public:
	CBigJason();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects, vector<CEnemyBullet*>* listBulletBoss);
	void Render();

	/* Keyboard */
	void OnKeyDown(int keycode);
	void OnKeyUp(int keycode);
	void KeyState();

	void CheckCollision(vector<LPGAMEOBJECT>* coObjects);
	void SetStartPos(float startx, float starty);

	void SetLevel(int l) { level = l; }
	void SetIsDead(bool _isDead) { isDead = _isDead; }
	void SetHealth(int hp) { health = hp; }
	int GetHealth() { return health; }
	int GetEnergy() { return energy; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void SetIsInjured(bool _injured) { isInjured = _injured; }
	int GetUntouchable() { return untouchable; }
	bool GetIsInjured() { return isInjured; }
	/* State */
	void SwitchState(CState* state);
	void set_bullet_list();

	int Get_BigJason_Normal_bullet();
	void AutoGo(float des);
	void Reset();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	static CBigJason* GetInstance();
	void Clear();
	void CheckCollisionWithBrick(vector<LPGAMEOBJECT>* coObjects);
	void CheckCollisionWithThorn(vector<LPGAMEOBJECT>* coObjects);
	void CheckCollisionWithEnemy(vector<LPGAMEOBJECT>* coObjects);
	void CheckCollisionWithItem(vector<LPGAMEOBJECT>* coObjects);
	void Revival();
	void SetHealthWithBullet(int bulletDame);
	/* Variable */
	CState* currentState;
	CAnimation* currentAni;
	bool renderFrame = false;
	int frameID;
	bool autoGoX = false;
	bool autoGoY = false;
};