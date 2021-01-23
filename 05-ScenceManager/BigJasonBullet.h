#pragma once
#include "BulletObject.h"
#include "Enemy.h"
#include "Brick.h"
#define OHSOPHIABULLET_FLYING_SPACE 120
struct Point
{
	float x;
	float y;

};
class BigJasonBullet : public BulletObject
{
	DWORD lastTime;
	float radius_increase;
	float angle;
	int bullet_direct_round; //0 thẳng, 1 phải, -1 trái
	Point point1, point2, point3, point4;
	int type;
	vector<BulletObject* > p_bullet_list;

public:
	BigJasonBullet();
	BigJasonBullet(float _start_x, float _start_y, int type,int direct_round );
	~BigJasonBullet();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
	void Set_Bullet_list();
	void Set_Bullet_Direct_Round(int direct) { bullet_direct_round = direct; }
	void Set_point();
	void Set_Type(int _type) { type = _type; }
	void CheckCollisionWithEnemy(vector<LPGAMEOBJECT>* coObjects);
	void CheckCollisionWithCBrick(vector<LPGAMEOBJECT>* coObjects);

};
