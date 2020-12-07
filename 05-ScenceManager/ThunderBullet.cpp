#include "ThunderBullet.h"

ThunderBullet::ThunderBullet(float _start_x, float _start_y)
{
	this->start_x = _start_x;
	this->start_y = _start_y;
	isMove = true;
	isDone = false;
	bulletDame = 1;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(17));
}

void ThunderBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (isDone) return;
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Enemy*>(coObjects->at(i)))
		{
			if (this->IsCollidingObject(coObjects->at(i)))
			{
				coObjects->at(i)->SetHp(bulletDame);
				isMove = false;
				isColEnemy = true;
			}

		}
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	//nếu không chết thì kiểm tra toàn bộ va chạm với các đối tượng khác
	CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed

	// No collision occured, proceed normally

	if (coEvents.size() == 0)  //nếu không có va chạm, update bình thường
	{
		x += dx;
		y += dy;
	}
	else //có va chạm
	{
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);  // sắp xếp lại các sự kiện va chạm đầu tiên theo trục x, y 

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Enemy*>(e->obj))
			{
				/*e->obj->SetState(DOMES_STATE_DIE);*/
			/*	x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;

				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;*/
				e->obj->SetHp(bulletDame);
				isMove = false;
				/*	isColBrick = true;*/
			}


			//else if (dynamic_cast<CGolem*>(e->obj))
			//{
			//	/*e->obj->SetState(DOMES_STATE_DIE);*/
			//	isMove = false;
			//}
		}


	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	/*y += 0.005f * dt;*/
	DebugOut(L"X, Y %f\n", x,y);
}

void ThunderBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDone)
	{
		if (animation_set->at(0)->GetCurrentFrame() == 0)
		{
			left = start_x;
			top = start_y;
			right = start_x + 15;
			bottom = start_y + 16;
			
		}
		if (animation_set->at(0)->GetCurrentFrame() == 1)
		{
			left = start_x;
			top = start_y;
			right = start_x + 15;
			bottom = start_y + 16*2;
		}
		if (animation_set->at(0)->GetCurrentFrame() == 2)
		{
			left = start_x;
			top = start_y;
			right = start_x + 15;
			bottom = start_y + 16*2;
		}
		if (animation_set->at(0)->GetCurrentFrame() == 3)
		{
			left = start_x;
			top = start_y - 16;
			right = start_x + 15;
			bottom = start_y + 16 * 4;
		}
		if (animation_set->at(0)->GetCurrentFrame() == 5)
		{
			left = start_x;
			top = start_y - 32;
			right = start_x + 15;
			bottom = start_y + 16 * 4;
		}
	
	}
}

void ThunderBullet::Render()
{
	int ani = 0;
	int alpha = rand() % (255 + 1) + 0;
	if (isDone) return;
	animation_set->at(0)->RenderThreeBullet(x, y,alpha);
	if (animation_set->at(0)->GetCurrentFrame() == animation_set->at(0)->GetLastFrame())
	{
		isDone = true;
	}
	RenderBoundingBox();
	
}
