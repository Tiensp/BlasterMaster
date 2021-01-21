#pragma once
#include "GameObject.h"
#include "State.h"
#include "GameDefine.h"
#include "BulletObject.h"

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

#define BIG_JASON_UNTOUCHABLE_TIME 5000


class CBigJason : public CGameObject
{
protected:
	static CBigJason* __instance;
	int level;
	int untouchable;
	DWORD untouchable_start;
	DWORD lifeTimeAni;

	float start_x;			// initial position of BigJason at scene
	float start_y;
	int energy=7;
	int health = 4;	// Máu nhân vật
	vector<BulletObject*> p_bullet_list;
public:
	CBigJason();
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
	int GetEnergy() { return energy; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	/* State */
	void SwitchState(CState* state);
	void set_bullet_list();
	int Get_BigJason_Normal_bullet();
	void Reset();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	static CBigJason* GetInstance();
	/* Variable */
	CState* currentState;
	CAnimation* currentAni;
	bool renderFrame;
	int frameID;
};