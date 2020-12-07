#include "ThreeBullet.h"

ThreeBullet::ThreeBullet(float _start_x, float _start_y, int _nx)
{
	bullet1 = new SophiaBullet(_start_x, _start_y);
	bullet1->SetPosition(_start_x, _start_y);
	bullet1->Set_bullet_dir(_nx);
	bullet1->Set_type(1);
	bullet1->SetAnimationSet(CAnimationSets::GetInstance()->Get(16));
	bullet2 = new SophiaBullet(_start_x, _start_y);
	bullet2->SetPosition(_start_x, _start_y);
	bullet2->Set_bullet_dir(_nx);
	bullet2->Set_type(1);
	bullet2->SetAnimationSet(CAnimationSets::GetInstance()->Get(16));
	bullet3 = new SophiaBullet(_start_x, _start_y);
	bullet3->SetPosition(_start_x, _start_y);
	bullet3->Set_bullet_dir(_nx);
	bullet3->Set_type(1);
	bullet3->SetAnimationSet(CAnimationSets::GetInstance()->Get(16));
	
	isMove = true;
	isDone = false;
}

void ThreeBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	CGameObject::Update(dt, coObjects);
	if (bullet1->isDone && bullet2->isDone && bullet3->isDone)
	{
		this->isDone = true;
	}
	if (bullet1->bullet_dir == 1)
	{
		bullet1->vx = 0.2f;
		/*	bullet1->x += bullet1->vx * dt;*/
		bullet2->vx = 0.2f;
		bullet2->vy = 0.05f;
		bullet3->vx = 0.2f;
		bullet3->vy = -0.05f;
	}
	else
	{
		bullet1->vx = -0.2f;
		bullet2->vx = -0.2f;
		bullet2->vy = 0.05f;
		bullet3->vx = -0.2f;
		bullet3->vy = -0.05f;
	}

	
	bullet1->Update(dt,coObjects);
	bullet2->Update(dt, coObjects);
	bullet3->Update(dt, coObjects);

	
	/*DebugOut(L"bullet1: %f\n", bullet1->dt);*/

	

}

void ThreeBullet::Render()
{
	int ani = 0;
	bullet1->Render();
	bullet2->Render();
	bullet3->Render();
	/*bullet1->Render();
	bullet2->Render();
	bullet3->Render();*/
}
