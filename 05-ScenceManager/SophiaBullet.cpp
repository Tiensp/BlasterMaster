#include "SophiaBullet.h"

SophiaBullet::SophiaBullet(float _start_x, float _start_y)
{
	/*this->x = 0;
	this->y = 0;*/
	this->start_x = _start_x;
	this->start_y = _start_y;
	isMove = true;
	isDone = false;
	bulletDame = 1;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(15));
}

SophiaBullet::~SophiaBullet()
{
}

void SophiaBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	BulletObject::Update(dt, coObjects);
	if (isDone) return;

	HandleMove(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3);
	
	if (type == 0)
	{
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
	
	}

}

void SophiaBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	if (!isDone)
	{
		left = x;
		right = x + 26;
		top = y;
		bottom = y + 8;
	}
}

void SophiaBullet::Render()
{
	int ani = 0;
	if (isDone) return;
	if (isColBrick)
	{
		ani = BULLETSOPHIA_STATE_ISCOL_BRICK;
		animation_set->at(ani)->Render(x, y);
		if (animation_set->at(ani)->GetCurrentFrame() == 2)
		{
			isDone = true;
		}
		return;
	}
	else if (isColEnemy) isDone = true;
	else if (isMove)
	{
		if (bullet_dir == 1)
		{
			ani = 0;
		}
		else if (bullet_dir == -1)
		{
			ani = 1;
		}
		else
		{
			ani = 2;
		}
	}


	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox(x,y);
}
