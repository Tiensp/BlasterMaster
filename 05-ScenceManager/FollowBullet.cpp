#include "FollowBullet.h"

FollowBullet::FollowBullet(float _start_x, float _start_y, CGameObject* _target)
{
	this->start_x = _start_x;
	this->start_y = _start_y;
	isMove = true;
	isDone = false;
	bulletDame = 1;
	target = _target;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(16));

}

FollowBullet::~FollowBullet()
{

}

void FollowBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	HandleMove(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3);
	//if (isDone) return;
	if (isMove)
	{
		if (this->y - target->y > 0)
		{
			vy = -0.05f;
			if (this->x - target->x > 0)
			{
				vx = -0.05f;
			}
			else
			{
				vx = 0.05f;
			}
		}
		else
		{
			vy = 0.05f;
			if (this->x - target->x > 0)
			{
				vx = -0.05f;
			}
			else
			{
				vx = 0.05f;
			}
		}
	}
	
	x += dx;
	y += dy;
	/*DebugOut(L"XFollow: %f\n",x);*/
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Enemy*>(coObjects->at(i)))
		{
			if (this->IsCollidingObject(coObjects->at(i)))
			{
				coObjects->at(i)->SetHp(bulletDame);
				isMove = false;
				isColEnemy = true;
				isDone = true;
			}

		}
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
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

			if (dynamic_cast<CBrick*>(e->obj)) // if e->obj is Goomba 
			{
				x += dx;
				y += dy;
			}
			else if (dynamic_cast<Enemy*>(e->obj))
			{
		
				e->obj->SetHp(bulletDame);
				isMove = false;
				isColEnemy = true;
				isDone = true;
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void FollowBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDone)
	{
		left = x;
		top = y;
		right = left + 10;
		bottom = top + 10;

	}
}

void FollowBullet::Render()
{
	int ani = 0;
	if (isDone) return;
	if (vx > 0) ani = 0;
	else ani = 1;
	animation_set->at(ani)->Render(x, y);
	DebugOut(L"XRender: %f, YRender: %f\n",x,y);

}
