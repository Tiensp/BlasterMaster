#include "BulletBoss.h"
BossBullet::BossBullet(float _start_x, float _start_y, int _nx)
{
	this->start_x = _start_x;
	this->start_y = _start_y;
	this->x = _start_x;

	bullet_dir = _nx;
	this->y = _start_y;
	isMove = true;
	isDone = false;
	bulletDame = 1;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(110));
}

BossBullet::~BossBullet()
{
}

void BossBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	CEnemyBullet::Update(dt, coObjects);

	
	HandleMove(SCREEN_HEIGHT / 3, SCREEN_HEIGHT / 3);
	if (isMove)
	{
		if (bullet_dir == 1)
		{
		/*	vx = 0.045f;*/
			vy = 0.0275f;
		}
		else if (bullet_dir == -1)
		{
			/*vx = -0.045f;*/
			vy = 0.0275f;
		}
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

				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;

				isColBrick = true;
				//isDone = true; 
			}
			else if (dynamic_cast<CBigJason*>(e->obj))
			{
				CBigJason::GetInstance()->SetHealthWithBullet(bulletDame);
				isColPlayer = true;
			}
		}


	}
	//for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];


}

void BossBullet::Render()
{
	int ani = 0;
	if (isDone) 
		return;
	if (isColBrick)
	{
		ani = 2;
		animation_set->at(ani)->Render(x, y);
		if (animation_set->at(ani)->GetCurrentFrame() == 0)
		{
			isDone = true;
		}
		return;
	}
	else if (isColPlayer)
	{
		ani = 2;
		animation_set->at(ani)->Render(x, y);
		if (animation_set->at(ani)->GetCurrentFrame() == 0)
		{
			isDone = true;
		}
		return;
	}
	else if (isMove)
	{
		if (bullet_dir == 1)
		{
			ani = 0;
		}
		else if (bullet_dir == -1)
		{
			ani = 1;
		}
	}
	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox(x,y);
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
