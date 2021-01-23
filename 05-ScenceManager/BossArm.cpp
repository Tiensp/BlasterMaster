#include "BossArm.h"

CBossArm::CBossArm(float x, float y, int type,float _vx, float _vy)
{
	hp = 999;
	this->x = x;
	this->y = y;
	this->typeArm = type;
	SetSpeed(_vx, _vy);
	new_vx = _vx;
	new_vy = _vy;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(121));
}

CBossArm::~CBossArm()
{
}

void CBossArm::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::Update(dt, coObjects);
	MoveFollow(x_follow, y_follow);
	x += dx;
	y += dy;
}

void CBossArm::Render()
{
	int ani;
	if (typeArm == 1)
	{
		ani = 0;
	}
	else
	{
		ani = 1;
	}
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox(x, y);
}

void CBossArm::MoveFollow(float x_follow, float y_follow)
{
	if (x < x_follow) vx = new_vx;
	else if (x > x_follow) vx = -new_vx;
	else vx = 0;

	if (y < y_follow) vy = new_vy;
	else if (y > y_follow) vy = -new_vy;
	else vy = 0;
}
