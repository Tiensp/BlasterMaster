#include "BulletBomb.h"


BombBullet::BombBullet(float _start_x, float _start_y)
{

	bullet1 = new BulletFloaters(_start_x, _start_y);
	bullet1->SetPosition(_start_x, _start_y);
	bullet1->SetAnimationSet(CAnimationSets::GetInstance()->Get(201));

	bullet2 = new BulletFloaters(_start_x, _start_y);
	bullet2->SetPosition(_start_x, _start_y);
	bullet2->SetAnimationSet(CAnimationSets::GetInstance()->Get(201));

	bullet3 = new BulletFloaters(_start_x, _start_y);
	bullet3->SetPosition(_start_x, _start_y);
	bullet3->SetAnimationSet(CAnimationSets::GetInstance()->Get(201));

	isMove = true;
	isDone = false;
}

BombBullet::~BombBullet()
{
}

void BombBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//HandleMove(SCREEN_HEIGHT / 6, SCREEN_HEIGHT / 6);

	if (bullet1->isDone || bullet2->isDone || bullet3->isDone) this->isDone = true;

	if (this->bullet_dir == -1)
	{
		bullet1->vx = -0.015f;
		bullet1->vy = -0.035f;
		bullet2->vx = 0.0f;
		bullet2->vy = -0.035f;
		bullet3->vx = 0.015f;
		bullet3->vy = -0.035f;
	}

	else if (this->bullet_dir == 1)
	{
		bullet1->vx = -0.005f;
		bullet1->vy = 0.025f;
		bullet2->vx = 0.0f;
		bullet2->vy = 0.025f;
		bullet3->vx = 0.005f;
		bullet3->vy = 0.025f;
	}

	bullet1->Update(dt, coObjects);
	bullet2->Update(dt, coObjects);
	bullet3->Update(dt, coObjects);

}

void BombBullet::Render()
{
	int ani = 0;

	bullet1->Render();
	bullet2->Render();
	bullet3->Render();

	//RenderBoundingBox(x,y);
}

void BombBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDone)
	{
		left = x;
		top = y;
		right = x + 10;
		bottom = y + 10;
	}
}