﻿#pragma once
#include "GameObject.h"
#include "State.h"
#include "GameDefine.h"

#define JASON_WALKING_SPEED		0.09f 
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

#define JASON_SMALL_BBOX_WIDTH  20
#define JASON_SMALL_BBOX_HEIGHT 31

#define JASON_BIG_BBOX_WIDTH  24
#define JASON_BIG_BBOX_HEIGHT 32

#define JASON_UNTOUCHABLE_TIME 5000


class CJason : public CGameObject
{
protected:
	static CJason* __instance;
	int level;
	int untouchable;
	DWORD untouchable_start;
	DWORD lifeTimeAni;

	float start_x;			// initial position of Jason at scene
	float start_y;

	bool isCrawling;
	bool isTouchingPortal;

	int health = 8;	// Máu nhân vật
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


	void Reset();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	static CJason* GetInstance();
	/* Variable */
	CState* currentState;
	CAnimation* currentAni;
	bool renderFrame;
	int frameID;
};