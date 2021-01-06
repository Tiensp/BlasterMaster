
#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "Enemy.h"

#define BULLET_SPEDD 0.25f
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
	bool isMove = false;
	LPANIMATION aniBullet;
	int bullet_dir;
	int bullet_type;
	bool isColBrick;
	bool isColEnemy;
	bool isDone;
	int bulletDame;
	
public:
	//BulletObject() {};
	~BulletObject() {}

	virtual void Render() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};



	void Set_IsMove(const bool& _isMove);
	bool Get_IsMove() const { return isMove; };
	void Set_bullet_dir(int bulletDir) { bullet_dir = bulletDir; }
	int Get_bullet_dir() { return bullet_dir; }
	void Set_bullet_type(int& bulletType) { bullet_type = bulletType; }
	void HandleMove(const float x_border, const float y_border);
	void CheckCollisionWithEnemy(vector<LPGAMEOBJECT>* coObjects);
	



};
//typedef BulletObject* LPSCENE;

