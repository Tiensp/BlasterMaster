#include "EnemyBullet.h"
#include "Sophia.h"
#include "Sound.h"

CEnemyBullet::~CEnemyBullet()
{
}

void CEnemyBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CheckCollisionWithPlayer(coObjects);
}

void CEnemyBullet::CheckCollisionWithPlayer(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	bool isColideUsingAABB = false;
	coEvents.clear();
	vector<LPGAMEOBJECT> ListEnemy;
	ListEnemy.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (dynamic_cast<CSophia*>(coObjects->at(i))||dynamic_cast<CBigJason*>(coObjects->at(i)))
		{
			ListEnemy.push_back(coObjects->at(i));
		}
	for (UINT i = 0; i < ListEnemy.size(); i++)
	{
		if (this->IsCollidingObject(ListEnemy.at(i)))
		{
			isColideUsingAABB = true;
			if (dynamic_cast<CSophia*>(coObjects->at(i)))
			{
				CSophia* sophia = dynamic_cast<CSophia*>(ListEnemy.at(i));
				sophia->SetHealthWithBullet(bulletDame);
				Sound::GetInstance()->Play("PlayerInjured", 0, 1);
				/*this->isMove = false;*/
				this->isDone = true;
			}
			else if (dynamic_cast<CBigJason*>(coObjects->at(i)))
			{
				CBigJason* bigJason = dynamic_cast<CBigJason*>(ListEnemy.at(i));
				bigJason->SetHealthWithBullet(bulletDame);
				Sound::GetInstance()->Play("PlayerInjured", 0, 1);
				/*this->isMove = false;*/
				this->isDone = true;
			}
			
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
				Sound::GetInstance()->Play("PlayerInjured", 0, 1);
			}
			else if (dynamic_cast<CBigJason*>(e->obj))
			{
				CSophia* sophia = dynamic_cast<CSophia*>(e->obj);
				sophia->SetHealthWithBullet(bulletDame);
				this->isDone = true;
				/*Item->IsDead = true;*/
			}
			

		}
	}
}

