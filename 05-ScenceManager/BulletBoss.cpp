#include "BulletBoss.h"
BossBullet::BossBullet(float _start_x, float _start_y, int _nx)
{
	/*this->start_x = _start_x;
	this->start_y = _start_y;
	isMove = true;
	isDone = false;
	bulletDame = 1;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(110));*/

	bullet1 = new BulletFloaters(_start_x, _start_y);
	bullet1->SetPosition(_start_x + 20, _start_y + 20);
	bullet1->Set_bullet_dir(_nx);
	bullet1->SetAnimationSet(CAnimationSets::GetInstance()->Get(110));

	bullet2 = new BulletFloaters(_start_x, _start_y);
	bullet2->SetPosition(_start_x + 20, _start_y + 20);
	bullet2->Set_bullet_dir(_nx);
	bullet2->SetAnimationSet(CAnimationSets::GetInstance()->Get(110));

	bullet3 = new BulletFloaters(_start_x, _start_y);
	bullet3->SetPosition(_start_x + 20, _start_y + 20);
	bullet3->Set_bullet_dir(_nx);
	bullet3->SetAnimationSet(CAnimationSets::GetInstance()->Get(110));

	bullet4 = new BulletFloaters(_start_x, _start_y);
	bullet4->SetPosition(_start_x + 20, _start_y + 20);
	bullet4->Set_bullet_dir(_nx);
	bullet4->SetAnimationSet(CAnimationSets::GetInstance()->Get(110));

	isMove = true;
	isDone = false;
}

BossBullet::~BossBullet()
{
}

void BossBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CEnemyBullet::Update(dt, coObjects);

	/*if (isDone) return;
	if (isMove)
	{
		if (bullet_dir == 1)
		{
			vx = 0.05f;
			vy = 0.15f;
		}
		else if (bullet_dir == -1)
		{
			vx = -0.05f;
			vy = 0.15f;
		}
	}
	else
	{
		return;
	}*/

	if (bullet1->isDone && bullet2->isDone && bullet3->isDone && bullet4->isDone) this->isDone = true;

	if (bullet1->bullet_dir == 1) {
		bullet1->vx = 0.07f;
		bullet1->vy = 0.15f;
		bullet2->vx = 0.07f;
		bullet2->vy = 0.1f;
		bullet3->vx = 0.07f;
		bullet3->vy = 0.075f;
		bullet4->vx = 0.07f;
		bullet4->vy = 0.05f;
	}
	else if (bullet1->bullet_dir == -1) {
		bullet1->vx = -0.07f;
		bullet1->vy = 0.15f;
		bullet2->vx = -0.07f;
		bullet2->vy = 0.1f;
		bullet3->vx = -0.07f;
		bullet3->vy = 0.075f;
		bullet4->vx = -0.07f;
		bullet4->vy = 0.05f;
	}

	bullet1->Update(dt, coObjects);
	bullet2->Update(dt, coObjects);
	bullet3->Update(dt, coObjects);
	bullet4->Update(dt, coObjects);

}

void BossBullet::Render()
{
	int ani = 0;
	//if (isDone) return;
	//if (isColPlayer)
	//{
	//	/*ani = 2;
	//	animation_set->at(ani)->Render(x, y);
	//	if (animation_set->at(ani)->GetCurrentFrame() == 0)
	//	{
	//		isDone = true;
	//	}*/
	//	isDone = true;
	//	return;
	//}
	
	/*if (isMove)
	{
	if (bullet_dir == 1)
	{
		ani = 0;
	}
	else if (bullet_dir == -1)
	{
		ani = 0;
	}
	}
	animation_set->at(ani)->Render(x, y);*/

	bullet1->Render();
	bullet2->Render();
	bullet3->Render();
	bullet4->Render();

	//RenderBoundingBox();
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
