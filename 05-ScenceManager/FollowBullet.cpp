#include "FollowBullet.h"

FollowBullet::FollowBullet(float _start_x, float _start_y, CGameObject* _target)
{
	this->start_x = _start_x;
	this->start_y = _start_y;
	isMove = true;
	isDone = false;
	bulletDame = 1;
	target = _target;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(16));

}

FollowBullet::~FollowBullet()
{

}

void FollowBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	BulletObject::Update(dt, coObjects);
	HandleMove(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3);
	//if (isDone) return;
	if (isMove)
	{
		if (this->y - target->y > 0)
		{
			vy = -0.05f;
			if (this->x - target->x > 0)
			{
				vx = -0.05f;
			}
			else
			{
				vx = 0.05f;
			}
		}
		else
		{
			vy = 0.05f;
			if (this->x - target->x > 0)
			{
				vx = -0.05f;
			}
			else
			{
				vx = 0.05f;
			}
		}
	}
	
	x += dx;
	y += dy;
}
void FollowBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDone)
	{
		left = x;
		top = y;
		right = left + 10;
		bottom = top + 10;

	}
}

void FollowBullet::Render()
{
	int ani = 0;
	if (isDone) return;
	if (vx > 0) ani = 0;
	else ani = 1;
	animation_set->at(ani)->Render(x, y);
	DebugOut(L"XRender: %f, YRender: %f\n",x,y);

}
