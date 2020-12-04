
#pragma once
#include "GameObject.h"

/*BULLET SOPHIA*/
#define BULLET_SPEED 0.25f
#define BULLETSOPHIA_ANI_RIGHT 0
#define BULLETSOPHIA_ANI_LEFT 1
#define BULLETSOPHI_ANI_UP	2
#define BULLETSOPHIA_ANI_ISCOL_BRICK 3
#define BULLETSOPHIA_STATE_ISCOL_BRICK 3

struct BulletObject;
typedef BulletObject* LPBulletObject;
class BulletObject : public CGameObject
{
public:
	float start_x;
	float start_y;
	float x_Border, y_Border;
	
	LPANIMATION aniBullet;
	
	
	int bullet_dir;
	int bullet_type;
	int bulletDame;
	int bullet_dir_x;
	int bullet_dir_y;

	bool isMove = false;
	bool isColBrick;
	bool isColEnemy;
	bool isColPlayer;
	bool isDone; 
	
public:
	BulletObject() {};
	~BulletObject() {}

	virtual void Render() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};



	void Set_IsMove(const bool& _isMove);
	bool Get_IsMove() const { return isMove; };
	void Set_bullet_dir(int bulletDir) { bullet_dir = bulletDir; }
	void Set_bullet_dir_xy(int bulletDir_x, int bulletDir_y) { bullet_dir_x = bulletDir_x, bulletDir_y = bulletDir_y; }
	int Get_bullet_dir() { return bullet_dir; }
	int Get_bullet_dir_xy() { return bullet_dir_x, bullet_dir_y; }
	void Set_bullet_type(int& bulletType) { bullet_type = bulletType; }
	void HandleMove(const float x_border, const float y_border);



};
//typedef BulletObject* LPSCENE;

