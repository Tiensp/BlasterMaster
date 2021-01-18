#include "JasonBullet.h"

JasonBullet::JasonBullet(float _start_x, float _start_y)
{
	this->start_x = _start_x;
	this->start_y = _start_y;
	isMove = true;
	isDone = false;
	bulletDame = 1;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(20));
}

JasonBullet::~JasonBullet()
{
}

void JasonBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	BulletObject::Update(dt, coObjects);
	HandleMove(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3);
	if (isDone) return;
	if (isMove)
	{
		if (bullet_dir == 1)
		{
			vx = BULLET_SPEED;
			vy = 0;
		}
		else if (bullet_dir == -1)
		{
			vx = -BULLET_SPEED;
			vy = 0;
		}
		else
		{
			vx = 0;
			vy = -BULLET_SPEED;
		}
	}
	else
	{
		return;
	}
}

void JasonBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDone)
	{
		left = x;
		top = y;
		right = x + 10;
		bottom = y + 10;
	}
}

void JasonBullet::Render()
{
	int ani = 0;
	if (isDone) return;
	animation_set->at(ani)->Render(x, y);

}
