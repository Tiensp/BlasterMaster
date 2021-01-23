#include "BulletBoss.h"
BossBullet::BossBullet(float _start_x, float _start_y, int _nx)
{
	this->start_x = _start_x;
	this->start_y = _start_y;
	this->x = _start_x;

	bullet_dir = _nx;
	this->y = _start_y;
	isMove = true;
	isDone = false;
	bulletDame = 1;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(110));
}

BossBullet::~BossBullet()
{
}

void BossBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	CEnemyBullet::Update(dt, coObjects);
	HandleMove(SCREEN_HEIGHT / 3, SCREEN_HEIGHT / 3);
	if (isMove)
	{
		if (bullet_dir == 1)
		{
			vx = 0.045f;
			vy = 0.0275f;
		}
		else if (bullet_dir == -1)
		{
			vx = -0.045f;
			vy = 0.0275f;
		}
	}
	else
	{
		return;
	}

	/*vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();*/
	/*CheckCollisionWithPlayer(coObjects);*/



}

void BossBullet::Render()
{
	int ani = 0;
	if (isDone)
		return;
	if (isColBrick)
	{
		ani = 2;
		animation_set->at(ani)->Render(x, y);
		if (animation_set->at(ani)->GetCurrentFrame() == 0)
		{
			isDone = true;
		}
		return;
	}
	else if (isColPlayer)
	{
		ani = 2;
		animation_set->at(ani)->Render(x, y);
		if (animation_set->at(ani)->GetCurrentFrame() == 0)
		{
			isDone = true;
		}
		return;
	}
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
	}
	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox(x, y);
}

void BossBullet::CheckCollisionWithPlayer(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	bool isColideUsingAABB = false;
	coEvents.clear();
	vector<LPGAMEOBJECT> ListEnemy;
	ListEnemy.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CBigJason*>(coObjects->at(i)))
		{
			ListEnemy.push_back(coObjects->at(i));
		}
	}

	for (UINT i = 0; i < ListEnemy.size(); i++)
	{
		if (this->IsCollidingObject(ListEnemy.at(i)))
		{

			if (dynamic_cast<CBigJason*>(coObjects->at(i)))
			{
				CBigJason* bigJason = dynamic_cast<CBigJason*>(ListEnemy.at(i));
				bigJason->SetHealthWithBullet(bulletDame);

				/*this->isMove = false;*/
				this->isDone = true;
			}
			isColideUsingAABB = true;

		}
	}
	if (isColideUsingAABB != true)
	{
		CalcPotentialCollisions(&ListEnemy, coEvents);
		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{

			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;

			// TODO: This is a very ugly designed function!!!!
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
			LPCOLLISIONEVENT e = coEventsResult[0];
			if (dynamic_cast<CBigJason*>(e->obj))
			{
				CBigJason* bigJason = dynamic_cast<CBigJason*>(e->obj);
				bigJason->SetHealthWithBullet(bulletDame);
			}
		}
	}
}

void BossBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDone)
	{
		left = x;
		top = y;
		right = x + 10;
		bottom = y + 10;
	}
}
