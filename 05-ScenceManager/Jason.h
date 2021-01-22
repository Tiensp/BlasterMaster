#pragma once
#include "GameObject.h"
#include "State.h"
#include "GameDefine.h"
#include "JasonBullet.h"
#include "Ladder.h"
#include "EnemyBullet.h"
#define JASON_WALKING_SPEED		0.09f 
#define JASON_CLIMB_SPEED		0.05f 
//0.1f
#define JASON_JUMP_SPEED_Y		0.5f
#define JASON_JUMP_DEFLECT_SPEED 0.2f

#define JASON_DIE_DEFLECT_SPEED	 0.5f

#define JASON_STATE_IDLE					100
#define JASON_STATE_WALKING_RIGHT			101
#define JASON_STATE_WALKING_LEFT			103
#define JASON_STATE_JUMP					104
#define JASON_STATE_GUN_UP					105
#define JASON_STATE_IDLE_GUN_UP			106
#define JASON_STATE_GUN_DOWN				107
#define JASON_STATE_TURN					108
#define JASON_STATE_DIE					130



#define JASON_ANI_DIE				1

#define	JASON_LEVEL_SMALL	1
#define	JASON_LEVEL_BIG		2

#define JASON_SMALL_BBOX_WIDTH  10
#define JASON_SMALL_BBOX_HEIGHT 17

#define JASON_BIG_BBOX_WIDTH  10
#define JASON_BIG_BBOX_HEIGHT 17

#define JASON_UNTOUCHABLE_TIME 5000


class CJason : public CGameObject
{
protected:
	static CJason* __instance;
	int level;
	int untouchable;
	bool isDead;
	int health;
	DWORD untouchable_start;
	DWORD lifeTimeAni;
	bool isColLadder;
	CLadder* Ladder = NULL;
	//CLadder* Ladder = NULL;

	D3DXVECTOR2 LadderPos;
	

	float start_x;			// initial position of Jason at scene
	float start_y;

	bool isCrawling;
	bool isTouchingPortal;
	bool jumpIntoCabin = false;
	bool isInjured = false;

		// Máu nhân vật
	vector<BulletObject* > p_bullet_list;
public:
	CJason();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	/* Keyboard */
	void OnKeyDown(int keycode);
	void OnKeyUp(int keycode);
	void KeyState();

	void SetStartPos(float startx, float starty);

	void SetLevel(int l) { level = l; }

	void SetHealth(int hp) { health = hp; }
	int GetHealth() { return health; }

	void SetIsCrawling(bool crawl) { isCrawling = crawl; }
	bool GetIsCrawling() { return isCrawling; }

	void SetIsTouchingPortal(bool touch) { isTouchingPortal = touch; }
	bool GetIsTouchingPortal() { return isTouchingPortal; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	
	/* State */
	void SwitchState(CState* state);

	void SetIsDead(bool _isDead) { isDead = _isDead; }
	void Reset();
	void ResetAtPos(float _x, float _y);
	void CheckCollisionWithBrick(vector<LPGAMEOBJECT>* coObjects);
	void CheckCollisionWithLadder(vector<LPGAMEOBJECT>* coObjects);
	void CheckCollisionWithEnemy(vector<LPGAMEOBJECT>* coObjects);
	void CheckCollisionWithThornOVW(vector<LPGAMEOBJECT>* coObjects);
	void CheckCollisionWithLava(vector<LPGAMEOBJECT>* coObjects);
	int Get_Jason_Normal_bullet();
	void set_bullet_list();
	vector<BulletObject*> Get_Bullet_List() { return p_bullet_list; }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	static CJason* GetInstance();
	void Clear();
	/* Variable */
	CState* currentState;
	CAnimation* currentAni;
	bool renderFrame;
	int frameID;
};