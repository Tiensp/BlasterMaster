#pragma once
#include "BossHand.h"
class CBossArm : public Enemy
{
	int typeArm; 
	float new_vx, new_vy;
	float x_follow, y_follow;
public:
	CBossArm(float x, float y, int type,float _vx, float _vy);
	~CBossArm();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		left = x;
		top = y;
		right = x + 16;
		bottom = y + 17;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void MoveFollow(float x_follow,float y_follow);
	void SetXYFollow(float x_follow, float y_follow) {
		this->x_follow = x_follow;
		this->y_follow = y_follow;
	}

};

