#pragma once
#include "Enemy.h"
#define BOSS_HAND_WALKING_SPEED_X 0.05f
#define BOSS_HAND_WALKING_SPEED_Y 0.05f
class CBossHand : public Enemy
{
	int typeHand;
	float x_boss, y_boss;
public:
	CBossHand(float x, float y, int type, float x_boss, float y_boss);
	~CBossHand();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		left = x;
		top = y;
		right = x + 18;
		bottom = y + 32;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void Move();
	void SetBossPos(float  x_boss, float y_boss);
};


