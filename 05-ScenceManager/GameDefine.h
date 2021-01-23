#pragma once
#include <Windows.h>
#include <dinput.h>
#include <WinUser.h> 

#include <stdlib.h> 
#include <stdarg.h> 
#include <stdio.h> 
#include <time.h> 
#include <unordered_map>

#include <d3d9.h>
#include <d3dx9.h>

#include "Utils.h"

using namespace std;

/*
	Kích thước cửa sổ dưới đây là kích thước dùng khởi tạo Window
	Kích thước thật sau khi tạo cửa số sẽ bị giảm đi so với tham số truyền vào
	vì window phải trừ cho borders và title bar. Theo mình đo được kích thước bị:
		-15 cho chiều rộng 
		-38 cho chiều cao
*/
#define SCREEN_WIDTH 271
#define SCREEN_HEIGHT 278

/////// SCENE  ////////
#define SCENE_TYPE_TITLE_SCENE 0
#define SCENE_TYPE_OPENING_CUTSCENE 1
#define SCENE_TYPE_ROLL_OUT_SCENE 2

#define ID_KHUNG_VIEN	16000
#define ID_BACKGROUND	16001

/////// CAMERA ////////
#define CAMERA_WIDTH 256
#define CAMERA_HEIGHT 240

#define W_CAM_BOUND 150

/////// SOPHIA ////////
#define SOPHIA_GRAVITY 0.001f
#define SOPHIA_JUMP_SPEED 0.36f

/////// PORTAL ///////
#define PORTAL_WIDTH	32
#define PORTAL_HEIGHT	32

/////// SYNTAX ///////
#define INSTANCE_SOPHIA CSophia::GetInstance()
#define INSTANCE_JASON CJason::GetInstance()
#define INSTANCE_BIGJASON CBigJason::GetInstance()

/////// STATE ////////
#define IDLE2WALK 0
#define WALK2IDLE 1
#define NORMAL_STATE 2 

/*
	Lí do sử dụng Extern có thể tìm hiểu qua mã lỗi LNK2005
*/
extern enum ObjectTAG
{
	NONE, //Default Object
	PLAYER,
	ENEMY,
	MISC,
	PORTAL,
	BULLET_ENEMIES,
};

extern enum ObjectTYPE
{
	/* PLAYER TYPE */
	SOPHIA = 0,
	JASON = 2,
	BIG_JASON = 3,

	/* MAP */
	MAPID = 10000,
	/* HP */
	Health = 50,
	HealthBar = 51,
	/* SELECT BULLET SCREEN */
	SELECT_BULLET = 54,

	/*ENEMIES*/
	GOLEM = 4,
	DOMES = 5,
	WORMS = 6,
	FLOATERS = 7,
	SKULLS = 8,
	INSECTS = 9,
	ORBS = 10,
	SHIPS = 11,
	EYEBALLS = 12,
	TELEPORTERS = 13,
	CANNONS = 14,
	TWISTERTUONG = 67,
	
	/*BOSS*/
	BOSS = 100,


	/* Portal */
	SpecialPortal = 400,
	OverWorld = 500,
	OverHead = 600
};

extern enum STATENAME
{
	/// Vì thứ tự ani trong aniset của các nhân vật có thể trùng nhau
	/// Ex: SOPHIA_IDLE_RIGHT == JASON_IDLE_RIGHT...
	/// Nên mình không dùng STATENAME làm kiểu dữ liệu cho thuộc tính StateName trong 
	/// class State vì sẽ ảnh hưởng vấn đề hiển thị
	/// Ex: BigJason->currState->StateName = SOPHIA_IDLE_RIGHT :vv
	/// Do đó mình chuyển sang dùng kiểu Int

	/* SOPHIA ANI */
	SOPHIA_IDLE_RIGHT = 0,
	SOPHIA_IDLE_LEFT = 4,
	SOPHIA_WALKING_RIGHT = 8,
	SOPHIA_WALKING_LEFT = 9,
	SOPHIA_TURN_RIGHT = 10,
	SOPHIA_TURN_LEFT = 11,
	SOPHIA_JUMP_RIGHT = 12,
	SOPHIA_JUMP_LEFT = 13,
	SOPHIA_JUMP_TURN_RIGHT = 14,
	SOPHIA_JUMP_TURN_LEFT = 15,
	SOPHIA_RAISED_GUN_RIGHT = 16,
	SOPHIA_RAISED_GUN_LEFT = 17,
	SOPHIA_IDLE_GUN_UP_RIGHT = 18,
	SOPHIA_IDLE_GUN_UP_LEFT = 19,
	SOPHIA_LOWERED_GUN_RIGHT = 20,
	SOPHIA_LOWERED_GUN_LEFT = 21,
	SOPHIA_WALKING_GUN_UP_RIGHT = 22,
	SOPHIA_WALKING_GUN_UP_LEFT = 23,
	SOPHIA_FALL_RIGHT = 24,
	SOPHIA_FALL_LEFT = 25,
	SOPHIA_FALL_TURN_RIGHT = 26,
	SOPHIA_FALL_TURN_LEFT = 27,
	SOPHIA_OPEN_CABIN_RIGHT = 28,
	SOPHIA_OPEN_CABIN_LEFT = 29,
	SOPHIA_DIE = 30,

	/* JASON */
	JASON_IDLE_RIGHT = 0,
	JASON_WALKING_RIGHT = 1,
	JASON_CRAWL_RIGHT = 2,
	JASON_SWIM_RIGHT = 3,
	JASON_CLIMB = 4,
	JASON_IDLE_LEFT = 5,
	JASON_WALKING_LEFT = 6,
	JASON_CRAWL_LEFT = 7,
	JASON_SWIM_LEFT = 8,
	JASON_DIE_RIGHT = 9,
	JASON_DIE_LEFT = 10,

	/* BIG JASON ANI */
	BIG_JASON_IDLE_RIGHT = 0,
	BIG_JASON_WALKING_RIGHT = 1,
	BIG_JASON_IDLE_LEFT = 2,
	BIG_JASON_WALKING_LEFT = 3,
	BIG_JASON_IDLE_TOP = 4,
	BIG_JASON_WALKING_TOP = 5,
	BIG_JASON_IDLE_BOT = 6,
	BIG_JASON_WALKING_BOT = 7,
	BIG_JASON_DIE = 8,
};

extern enum ANISET_OBJ
{
	/* HP */
	ANISET_HP = 0,
	ANISET_HP_BAR = 0,
};

extern enum ITEM_OBJ
{
	HPITEM = 0,
	FOLLOWBULLET = 1,
	THUNDERBULLET =2,
	THREEBULLET = 3,
	POWER = 4

};

extern enum SCENE_TYPE
{
	SCENE_TYPE_INTRO = 0,
	SCENE_TYPE_OVERWORLD = 1,
	SCENE_TYPE_OVERHEAD = 2,
	SCENE_TYPE_ENDSCENE = 3
};



///Game Global
extern std::unordered_map<int, bool> _KEYCODE;
extern std::unordered_map<ObjectTYPE, bool> _ACTIVE;

class GameDefine
{
public:
	GameDefine() {};
	~GameDefine() {};
};