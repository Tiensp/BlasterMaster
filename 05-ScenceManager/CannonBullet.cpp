#include "CannonBullet.h"

CCannonBullet::CCannonBullet(float _start_x, float _start_y)
{
	this->start_x = _start_x;
	this->start_y = _start_y;
	this->SetPosition(start_x, start_y);
	isMove = true;
	isDone = false;
	bulletDame = 1;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(20));
}

CCannonBullet::~CCannonBullet()
{
	
}

void CCannonBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CEnemyBullet::Update(dt,coObjects);
	
	if (isDone) return;

	HandleMove(SCREEN_HEIGHT / 3, SCREEN_HEIGHT / 3);
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
		else if(bullet_dir == 2)
		{
			vx = 0;
			vy = BULLET_SPEED;
		}
		else if (bullet_dir == -2)
		{
			vx = 0;
			vy = -BULLET_SPEED;
		}
	}
	//x += dx;
	//y += dy;
	
		

	
	

}

void CCannonBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDone)
	{
		left = x;
		top = y;
		right = x + 10;
		bottom = y + 10;
	}
}

void CCannonBullet::Render()
{
	int ani = 0;
	if (isDone) return;
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox(x, y);
}
