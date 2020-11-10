#pragma once
#include "GameObject.h"

#define SOPHIA_WALKING_SPEED		0.09f 
//0.1f
#define SOPHIA_JUMP_SPEED_Y		0.5f
#define SOPHIA_JUMP_DEFLECT_SPEED 0.2f
#define SOPHIA_GRAVITY			0.002f
#define SOPHIA_DIE_DEFLECT_SPEED	 0.5f

#define SOPHIA_STATE_IDLE					100
#define SOPHIA_STATE_WALKING_RIGHT			101
#define SOPHIA_STATE_WALKING_LEFT			103
#define SOPHIA_STATE_JUMP					104
#define SOPHIA_STATE_GUN_UP					105
#define SOPHIA_STATE_IDLE_GUN_UP			106
#define SOPHIA_STATE_GUN_DOWN				107
#define SOPHIA_STATE_TURN					108
#define SOPHIA_STATE_DIE					130

#define SOPHIA_ANI_IDLE_RIGHT			0
#define SOPHIA_ANI_IDLE_LEFT			4
#define SOPHIA_ANI_SMALL_IDLE_RIGHT			2
#define SOPHIA_ANI_SMALL_IDLE_LEFT			3

#define SOPHIA_ANI_WALKING_RIGHT		8
#define SOPHIA_ANI_WALKING_LEFT			9
#define SOPHIA_ANI_SMALL_WALKING_RIGHT		6
#define SOPHIA_ANI_SMALL_WALKING_LEFT		7
#define SOPHIA_ANI_TURN_RIGHT				10
#define SOPHIA_ANI_TURN_LEFT				11
#define SOPHIA_ANI_JUMP_RIGHT				12
#define SOPHIA_ANI_JUMP_LEFT				13
#define SOPHIA_ANI_GUN_UP_RIGHT				16
#define SOPHIA_ANI_GUN_UP_LEFT				17
#define SOPHIA_ANI_IDLE_GUN_UP_RIGHT		18
#define	SOPHIA_ANI_IDLE_GUN_UP_LEFT			19
#define SOPHIA_ANI_GUN_DOWN_RIGHT			20
#define SOPHIA_ANI_GUN_DOWN_LEFT			21

#define SOPHIA_ANI_DIE				1

#define	SOPHIA_LEVEL_SMALL	1
#define	SOPHIA_LEVEL_BIG		2

#define SOPHIA_BIG_BBOX_WIDTH  26
#define SOPHIA_BIG_BBOX_HEIGHT 18

#define SOPHIA_SMALL_BBOX_WIDTH  13
#define SOPHIA_SMALL_BBOX_HEIGHT 15

#define SOPHIA_UNTOUCHABLE_TIME 5000


class CSophia : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Sophia at scene
	float start_y; 

	bool raisedGun;
	bool isTurning;
	bool isJumping;

	bool DoneTurn;
	bool DoneGunUp;		
	bool DoneGunDown;

	DWORD lifeTimeJump;
	DWORD lifeTimeGunUp;
	DWORD lifeTimeGunDown;
	DWORD lifeTimeTurn;
public: 
	CSophia(float x = 100.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();

	bool GetDoneGunUp() { return DoneGunUp; }
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void SetIsTurning(bool turn) { isTurning = turn; }
	void SetIsJumping(bool jump) { isJumping = jump; }
	void SetDoneGunUp(bool done) { DoneGunUp = done; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	/* Actions */


	void Reset();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};