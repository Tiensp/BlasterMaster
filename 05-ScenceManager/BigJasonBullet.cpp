#include "BigJasonBullet.h"

BigJasonBullet::BigJasonBullet(float _start_x, float _start_y)
{

	this->start_x = _start_x;
	this->start_y = _start_y;
	isMove = true;
	isDone = false;
	bulletDame = 1;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(19));
}

BigJasonBullet::~BigJasonBullet()
{
}

void BigJasonBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
		else if (bullet_dir == 3)
		{
			vx = 0;
			vy = -BULLET_SPEED;
		}
		else if (bullet_dir == 4)
		{
			vx = 0;
			vy = BULLET_SPEED;
		}
	}
}

void BigJasonBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	if (!isDone)
	{
		left = x;
		right = x + 10;
		top = y;
		bottom = y + 10;
	}
}

void BigJasonBullet::Render()
{
	int ani = 0;
	if (isDone) return;
	else if (isColEnemy) isDone = true;
	else if (isMove)
	{
		if (bullet_dir == 1)
		{
			ani = 2;	
		}
		else if (bullet_dir == -1)
		{
			ani = 0;
		}
		else if (bullet_dir == 3)
		{
			ani = 1;
		}
		else if (bullet_dir == 4)
		{
			ani = 3;
		}
	}
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox(x,y);
}
