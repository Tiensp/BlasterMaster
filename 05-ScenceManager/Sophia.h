#pragma once
#include "GameObject.h"
#include "State.h"
#include "GameDefine.h"

#define SOPHIA_WALKING_SPEED		0.09f 
//0.1f
#define SOPHIA_JUMP_SPEED_Y		0.5f
#define SOPHIA_JUMP_DEFLECT_SPEED 0.2f

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

#define SOPHIA_ANI_SMALL_WALKING_RIGHT		6
#define SOPHIA_ANI_SMALL_WALKING_LEFT		7



#define SOPHIA_ANI_DIE				1

#define	SOPHIA_LEVEL_SMALL	1
#define	SOPHIA_LEVEL_BIG		2

#define SOPHIA_SMALL_BBOX_WIDTH  26
#define SOPHIA_SMALL_BBOX_HEIGHT 18

#define SOPHIA_BIG_BBOX_WIDTH  26
#define SOPHIA_BIG_BBOX_HEIGHT 34

#define SOPHIA_UNTOUCHABLE_TIME 5000


class CSophia : public CGameObject
{
protected:
	static CSophia* __instance;
	int level;
	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Sophia at scene
	float start_y; 

	bool isGunUp;
	bool isRaisedGun;
	bool isLoweredGun;
	bool isTurning;
	bool isJumping;
	bool isFalling;

	bool DoneTurn;
	bool DoneGunUp;		
	bool DoneGunDown;

	DWORD lifeTimeAni;
public: 
	CSophia();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();

	/* Keyboard */
	void OnKeyDown(int keycode);
	void OnKeyUp(int keycode);
	void KeyState();

	void SetStartPos(float startx, float starty);
	bool GetDoneTurn() { return DoneTurn; }
	bool GetDoneGunUp() { return DoneGunUp; }
	//void SetState(int state);
	void SetLevel(int l) { level = l; }

	void SetIsTurning(bool turn) { isTurning = turn; }
	bool GetIsTurning() { return isTurning; }

	void SetIsRaisedGun(bool raisedgun) { isRaisedGun = raisedgun; }
	bool GetIsRaisedGun() { return isRaisedGun; }

	void SetIsLoweredGun(bool loweredgun) { isLoweredGun = loweredgun; }
	bool GetIsLoweredGun() { return isLoweredGun; }

	void SetIsJumping(bool jump) { isJumping = jump; }
	bool GetIsJumping() { return isJumping; }
	void SetIsGunUp(bool gunup) { isGunUp = gunup; }
	bool GetIsGunUp() { return isGunUp; }
	void SetIsFalling(bool fall) { isFalling = fall; }
	bool GetIsFalling() { return isFalling; }
	void SetDoneGunUp(bool done) { DoneGunUp = done; }
	void SetDoneTurn(bool done) { DoneTurn = done; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	/* State */
	void SwitchState(CState* state);


	void Reset(float _startx = 0.0f , float _starty = 0.0f);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	static CSophia* GetInstance();
	/* Variable */
	CState* currentState;
	CAnimation* currentAni;
	bool renderFrame;
	int frameID;
};