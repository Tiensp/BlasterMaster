#include "FollowBullets.h"


FollowBullets::FollowBullets(float _start_x, float _start_y, vector<LPGAMEOBJECT>* target)
{
	this->start_x = _start_x;
	this->start_y = _start_y;
	isMove = true;
	isDone = false;
	bulletDame = 1;
	for (int i = 0; i < target->size(); i++)
	{
		if (dynamic_cast<Enemy*>(target->at(i)))
		{
			BulletObject* p_bullet = new FollowBullet(_start_x, _start_y, target->at(i));
			p_bullet->SetPosition(start_x, start_y);
			p_bullet->Set_IsMove(true);
			listFollowBullet.push_back(p_bullet);
		}
	}
}

FollowBullets::~FollowBullets()
{
}

void FollowBullets::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	BulletObject::Update(dt, coObjects);

	for (int i = 0; i < listFollowBullet.size(); i++)
	{
		listFollowBullet.at(i)->Update(dt, coObjects);
	}
	
}

void FollowBullets::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}

void FollowBullets::Render()
{
	for (int i = 0; i < listFollowBullet.size(); i++)
	{
		listFollowBullet.at(i)->Render();
	}
}
