#include "SophiaBullet.h"

SophiaBullet::SophiaBullet(float _start_x, float _start_y)
{
	/*this->x = 0;
	this->y = 0;*/
	this->start_x = _start_x;
	this->start_y = _start_y;
	isMove = true;
	isDone = false;
	bulletDame = 1;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(15));
}

SophiaBullet::~SophiaBullet()
{
}

void SophiaBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	HandleMove(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3);
	if (isDone) return;
	if (type == 0)
	{
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
			else
			{
				vx = 0;
				vy = -BULLET_SPEDD;
			}
		}
		else
		{
			return;
		}
	}
	CheckCollisionWithEnemy(coObjects);
	//for (int i = 0; i < coObjects->size(); i++)
	//{
	//		if (this->IsCollidingObject(coObjects->at(i)))
	//		{
	//			if (dynamic_cast<Enemy*>(coObjects->at(i)))
	//			{
	//				coObjects->at(i)->SetHp(bulletDame);
	//				isMove = false;
	//				isColEnemy = true;
	//			}
	//			else
	//			{
	//				x += dx;
	//				y += dy;
	//			}
	//		}
	//}

	//vector<LPCOLLISIONEVENT> coEvents;
	//vector<LPCOLLISIONEVENT> coEventsResult;

	//coEvents.clear();

	//// turn off collision when die 
	////nếu không chết thì kiểm tra toàn bộ va chạm với các đối tượng khác
	//CalcPotentialCollisions(coObjects, coEvents);

	//// reset untouchable timer if untouchable time has passed

	//// No collision occured, proceed normally

	//if (coEvents.size() == 0)  //nếu không có va chạm, update bình thường
	//{
	//	x += dx;
	//	y += dy;
	//}
	//else //có va chạm
	//{
	//	float min_tx, min_ty, nx = 0, ny = 0;
	//	float rdx = 0;
	//	float rdy = 0;

	//	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);  // sắp xếp lại các sự kiện va chạm đầu tiên theo trục x, y 

	//	for (UINT i = 0; i < coEventsResult.size(); i++)
	//	{
	//		LPCOLLISIONEVENT e = coEventsResult[i];

	//		if (dynamic_cast<CBrick*>(e->obj)) // if e->obj is Goomba 
	//		{
	//			if (this->type == 0)
	//			{
	//				x += min_tx * dx + nx * 0.4f;
	//				y += min_ty * dy + ny * 0.4f;
	//				isColBrick = true;
	//			}
	//			else
	//			{
	//				x += dx;
	//				y += dy;
	//			}
	//		
	//		}
	//		else if (dynamic_cast<Enemy*>(e->obj))
	//		{
	//			e->obj->SetHp(bulletDame);
	//			isMove = false;
	//			isColEnemy = true;
	//		}


	//	
	//	}


	//}
	//for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void SophiaBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	if (!isDone)
	{
		left = x;
		right = x + 26;
		top = y;
		bottom = y + 8;
	}
}

void SophiaBullet::Render()
{
	int ani = 0;
	if (isDone) return;
	if (isColBrick)
	{
		ani = BULLETSOPHIA_STATE_ISCOL_BRICK;
		animation_set->at(ani)->Render(x, y);
		if (animation_set->at(ani)->GetCurrentFrame() == 2)
		{
			isDone = true;
		}
		return;
	}
	else if (isColEnemy) isDone = true;
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
		else
		{
			ani = 2;
		}
	}


	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox(x,y);
}
