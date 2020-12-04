#include "BulletFloaters.h"
BulletFloaters::BulletFloaters(float _start_x, float _start_y)
{
	this->start_x = _start_x;
	this->start_y = _start_y;
	isMove = true;
	isDone = false;
	bulletDame = 1;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(16));
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
		/*if (bullet_dir_x == 1 && bullet_dir_y == 1)
		{
			vx = 0.25f;
			vy = 0.2f;
		}
		else if (bullet_dir_x == -1 && bullet_dir_y == 1)
		{
			vx = -0.25f;
			vy = 0.2f;
		}*/
		vx = 0.25f;
		vy = 0.2f;
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
				//isDone = true; 
			}
			else if (e->obj->objTag == ENEMY)
			{
				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;
			}
			else if (e->obj->objTag == Player)
			{
				isColPlayer = true;
				/*x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;*/
			}
		}


	}
	//for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void BulletFloaters::Render()
{
	int ani = 0;
	if (isDone) return;
	if (isColBrick)
	{
		ani = BULLET_FLOATER_ANI_COLLISON;
		animation_set->at(ani)->Render(x, y);
		if (animation_set->at(ani)->GetCurrentFrame() == 0)
		{
			isDone = true;
		}
		return;
	}
	else if (isColPlayer)
	{
		ani = BULLET_FLOATER_ANI_COLLISON;
		animation_set->at(ani)->Render(x, y);
		if (animation_set->at(ani)->GetCurrentFrame() == 0)
		{
			isDone = true;
		}
		return;
	}
	else if (isMove)
	{
		vx = 0.25f;
		vy = 0.2f;
		/*if (bullet_dir_x == 1 && bullet_dir_y == 1)
		{
			ani = BULLET_FLOATER_ANI_WALKING_RIGHT_DOWN;
		}
		else if (bullet_dir == -1 && bullet_dir_y == 1)
		{
			ani = BULLET_FLOATER_ANI_WALKING_LEFT_DOWN;
		}*/
	}
	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
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
