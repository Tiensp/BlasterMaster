#pragma once
#include "GameObject.h"
#include "State.h"
#include "GameDefine.h"
#include "SophiaBullet.h"
#include "Health.h"
#include "BulletObject.h"
#include "ThreeBullet.h"
#include "ThunderBullet.h"
#include "FollowBullets.h"
#include "Item.h"
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

#define SOPHIA_OPEN_CABIN_BBOX_HEIGHT 26

#define SOPHIA_BIG_BBOX_WIDTH  26
#define SOPHIA_BIG_BBOX_HEIGHT 34

#define SOPHIA_UNTOUCHABLE_TIME 3000


class CSophia : public CGameObject
{
protected:
	static CSophia* __instance;
	int level;
	int untouchable;
	DWORD untouchable_start;
	DWORD lifeTimeAni;
	DWORD lastFrameTime;

	float start_x;			// initial position of Sophia at scene
	float start_y; 

	bool isWalking;
	bool isGunUp;
	bool isRaisedGun;
	bool isLoweredGun;
	bool isTurning;
	bool isJumping;
	bool isFalling;
	bool isAllowFire = true;
	bool isInjured = false;

	bool isAutoGo = false;
	bool isColliBrick;
	bool isFrozen = false;
	bool isOpenCabin = false;
	float autoGoDes;
	int numberThreeBullet = 5;
	int numberThunderBullet = 5;
	int numberFollowBullet = 5;
	int health = 8;	// Máu nhân vật

	float lastColliBrick_y = NULL;
	bool isSetFollowBullet;
	float rectL, rectT, rectR, rectB;
	vector<BulletObject* > p_bullet_list;
	vector<LPGAMEOBJECT> list_enemy_contain;
public: 
	CSophia();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();

	/* Keyboard */
	void OnKeyDown(int keycode);
	void OnKeyUp(int keycode);
	void KeyState();

	void SetStartPos(float startx, float starty);

	void SetLevel(int l) { level = l; }

	void SetIsWalking(bool walk) { isWalking = walk; }
	bool GetIsWalking() { return isWalking; }

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
	int GetUntouchable() { return untouchable; }

	void SetIsInjured(bool _injured) { isInjured = _injured; }
	bool GetIsInjured() { return isInjured; }

	void SetHealth(int hp) { health = hp; }
	void SetHealthWithBullet(int dame) { health -= dame; }
	int GetHealth() { return health; }

	void SetIsAutoGo(bool autoGo) { isAutoGo = autoGo; }
	bool GetIsAutoGo() { return isAutoGo; }

	void SetIsFrozen(bool frozen) { isFrozen = frozen; }
	bool GetIsFrozen() { return isFrozen; }

	void SetIsOpenCabin(bool open) { isOpenCabin = open; }
	bool GetIsOpenCabin() { return isOpenCabin; }


	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	/* State */
	void SwitchState(CState* state, int changeType);


	void Reset();
	void ResetAtPos(float _x, float _y);

	void AutoGo(float x_des);
	void set_bullet_list();
	int Get_Sophia_Normal_bullet();
	bool AllowFire();
	void RenderOPENCabinAni();
	D3DCOLOR GetRENDERColor();
	
	vector<BulletObject*> Get_Bullet_List()  { return p_bullet_list; }
	void CheckCollisionWithBrick(vector<LPGAMEOBJECT>* coObjects);
	void CheckCollisionWithPortal(vector<LPGAMEOBJECT>* coObjects);
	void CheckCollisionWithItem(vector<LPGAMEOBJECT>* coObjects);
	void CheckCollisionWithEnemy(vector<LPGAMEOBJECT>* coObjects);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	static CSophia* GetInstance();
	void Clear();
	/* Variable */
	CState* currentState;
	CAnimation* currentAni;
	
	bool renderFrame;	// Biến renderFrame để xác định khi nào cần render 1 frame

	int frameID;
	int colorID = 0;
	int wheelID = 0;
	int changeStateType = NORMAL_STATE;

	float x_render;		// Vì sophia có cần render vị trí cho từng hình nên mình dùng 
	float y_render;		// x/y_render làm pos render thay vì đổi trực tiếp tọa độ x,y
};