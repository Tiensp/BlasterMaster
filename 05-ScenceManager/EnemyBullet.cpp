#include "EnemyBullet.h"
#include "Sophia.h"

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
	vector<LPGAMEOBJECT> player;
	player.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (dynamic_cast<CSophia*>(coObjects->at(i)))
		{
			player.push_back(coObjects->at(i));
		}
	for (UINT i = 0; i < player.size() && isColideUsingAABB == false; i++)
	{
		if (this->IsCollidingObject(player.at(i)))
		{
			isColideUsingAABB = true;
			CSophia* sophia = dynamic_cast<CSophia*>(player.at(i));
			sophia->SetHealthWithBullet(this->bulletDame);
			/*this->isMove = false;*/
			this->isColEnemy = true;
			this->isDone = true;
		}

	}
	if (isColideUsingAABB != true)
	{
		CalcPotentialCollisions(&player, coEvents);
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
			CSophia* sophia = dynamic_cast<CSophia*>(e->obj);
			sophia->SetHealthWithBullet(this->bulletDame);
			this->isDone = true;

		}
	}
}

