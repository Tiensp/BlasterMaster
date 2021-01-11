#include "BulletObject.h"
#include "Sophia.h"
#include "Brick.h"
#include "Enemy.h"



void BulletObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	/*CheckCollisionWithEnemy(coObjects);*/
}

void BulletObject::Set_IsMove(const bool& _isMove)
{
	this->isMove = _isMove;
}

void BulletObject::HandleMove(const float x_border, const float y_border)
{
	if (x > start_x + x_border || x < start_x - x_border || y < start_y - y_border || y > start_y + y_border)
	{
	/*	isMove = false;*/
		isDone = true;
	}

}

void BulletObject::CheckCollisionWithEnemy(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	bool isColideUsingAABB = false;
	coEvents.clear();
	vector<LPGAMEOBJECT> ListEnemy;
	ListEnemy.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (dynamic_cast<Enemy*>(coObjects->at(i)))
		{
			ListEnemy.push_back(coObjects->at(i));
		}
	for (UINT i = 0; i < ListEnemy.size() && isColideUsingAABB ==false; i++)
	{
		if (this->IsCollidingObject(ListEnemy.at(i)))
		{
			isColideUsingAABB = true;
			Enemy* enemy = dynamic_cast<Enemy*>(ListEnemy.at(i));
			enemy->Set_hp(bulletDame);
			/*this->isMove = false;*/
			this->isColEnemy = true;
			this->isDone = true;
		}

	}
	if (isColideUsingAABB != true)
	{
		CalcPotentialCollisions(&ListEnemy, coEvents);
		if (coEvents.size() == 0)
		{
			/*x += dx;
			y += dy;*/
		}
		else
		{

			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;

			// TODO: This is a very ugly designed function!!!!
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
			LPCOLLISIONEVENT e = coEventsResult[0];
			Enemy* enemy = dynamic_cast<Enemy*>(e->obj);
			enemy->Set_hp(bulletDame);
			this->isDone = true;
			/*Item->IsDead = true;*/
			
		}
	}
}

