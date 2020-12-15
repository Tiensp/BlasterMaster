#include "BigJasonBullet.h"

BigJasonBullet::BigJasonBullet(float _start_x, float _start_y)
{

	this->start_x = _start_x;
	this->start_y = _start_y;
	isMove = true;
	isDone = false;
	bulletDame = 1;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(19));
}

BigJasonBullet::~BigJasonBullet()
{
}

void BigJasonBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	HandleMove(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3);
	if (isDone) return;
	if (isMove)
	{
		if (bullet_dir == 1)
		{
			vx = BULLET_SPEDD;
			vy = 0;
		}
		else if (bullet_dir == -1)
		{
			vx = -BULLET_SPEDD;
			vy = 0;
		}
		else if (bullet_dir == 3)
		{
			vx = 0;
			vy = -BULLET_SPEDD;
		}
		else if (bullet_dir == 4)
		{
			vx = 0;
			vy = BULLET_SPEDD;
		}
	}


	
		
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
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void BigJasonBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	if (!isDone)
	{
		left = x;
		right = x + 10;
		top = y;
		bottom = y + 10;
	}
}

void BigJasonBullet::Render()
{
	int ani = 0;
	if (isDone) return;
	else if (isColEnemy) isDone = true;
	else if (isMove)
	{
		if (bullet_dir == 1)
		{
			ani = 2;	
		}
		else if (bullet_dir == -1)
		{
			ani = 0;
		}
		else if (bullet_dir == 3)
		{
			ani = 1;
		}
		else if (bullet_dir == 4)
		{
			ani = 3;
		}
	}
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox(x,y);
}
