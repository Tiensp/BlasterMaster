#include "BulletFloaters.h"
//#include "BulletFloaters.h"
//
//BulletFloaters::BulletFloaters(float x, float y)
//{
//	/*vx = 0.5f;
//	vy = 0.5f;*/
//	this->x = x;
//	this->y = y;
//	aniBullet = CAnimations::GetInstance()->Get(BULLET_FLOATERS_ANI);
//	
//}
//
//BulletFloaters::~BulletFloaters()
//{
//}
//
//void BulletFloaters::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
//{
//	//BulletObject::Update(dt, coObjects);
//	this->dt = dt;
//	dx = 0.05f * dt;
//	//dy = 0.05f * dt;
//	x += dx;
//	y += dy;
//
//	
//
//
//}
//
//void BulletFloaters::Render()
//{
//	RenderBoundingBox();
//	aniBullet->Render(x,y);
//
//
//}
//
//void BulletFloaters::GetBoundingBox(float& left, float& top, float& right, float& bottom)
//{
//	left = x;
//	top = y;
//	right = x + 10;
//	bottom = y + 10;
//	
//}

BulletFloaters::BulletFloaters(float _start_x, float _start_y)
{
	this->start_x = _start_x;
	this->start_y = _start_y;
	isMove = true;
	isDone = false;
	bulletDame = 1;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(20));
}

BulletFloaters::~BulletFloaters()
{
}

void BulletFloaters::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (isDone) return;

	if (isMove)
	{
		vx = 0.25f;
		vy = 0.1f;
	}
	else
	{
		return;
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

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);  // sắp xếp lại các sự kiện va chạm đầu tiên theo trục x, y 

		

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBrick*>(e->obj)) // if e->obj is Goomba 
			{
				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;

				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
				isColBrick = true;
				isDone = true; 
			}
			
		}


	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void BulletFloaters::Render()
{
	int ani = 0;
	if (isDone) return;
	animation_set->at(ani)->Render(x, y);
}

void BulletFloaters::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDone)
	{
		left = x;
		top = y;
		right = x + 10;
		bottom = y + 10;
	}
}

