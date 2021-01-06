#include "BulletSkull.h"
BulletSkull::BulletSkull(float _start_x, float _start_y, LPGAMEOBJECT player)
{
	this->start_x = _start_x;
	this->start_y = _start_y;
	this->target = player;
	isMove = true;
	isDone = false;
	bulletDame = 1;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(21));
}

BulletSkull::~BulletSkull()
{
}

void BulletSkull::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (isDone) return;

	if (isMove)
	{
		if (bullet_dir == 1 && ny != 0)
		{
			vx = 0.505f;
			vy = -0.505f;
		}
		else if (bullet_dir == -1 && ny != 0)
		{
			vx = -0.505f;
			vy = -0.505f;
		}
		else if(bullet_dir == 1)
		{
			vx = 0.205f;
			vy = 0;
		}
		else if (bullet_dir == -1)
		{
			vx = -0.205f;
			vy = 0;
		}
		else
		{
			vx = 0;
			vy = 0.075f;
		}
	}
	else
	{
		return;
	}


	if (this->x - target->x <= 0)
	{
		nx = 1;
	}
	else if (this->x - target->x > 0)
	{
		nx = -1;
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

		timer += interval;

		if (timer == timeToExplosive)
		{
			if (this->GetState() == 1 || this->GetState() == 3)
			{
				this->SetState(5);
			}
			else if (this->GetState() == 2 || this->GetState() == 4)
			{
				this->SetState(5);
			}
			timer = 0;
		}

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
				/*x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;*/

				/*if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;*/

				//isDone = true; 
				if (e->ny < 0)
				{
					if (this->nx > 0)
					{
						if (this->GetState() == 0)
						{
							this->SetState(1);
						}	
						else this->SetState(3);
					}
					else if (this->nx < 0)
					{
						if (this->GetState() == 0)
						{
							this->SetState(2);
						}
						else this->SetState(4);
					}
				}
			}
			else if (e->obj->objTag == ENEMY)
			{
				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;
			}
			else if (e->obj->objTag == PLAYER)
			{
				isColPlayer = true;
				/*x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;*/
			}
		}


	}
	//for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void BulletSkull::Render()
{
	int ani = 0;
	if (isDone) return;
	if (isColBrick)
	{
		ani = 5;
		animation_set->at(ani)->Render(x, y);
		if (animation_set->at(ani)->GetCurrentFrame() == 0)
		{
			isDone = true;
		}
		return;
	}
	else if (isColPlayer)
	{
		ani = 5;
		animation_set->at(ani)->Render(x, y);
		if (animation_set->at(ani)->GetCurrentFrame() == 0)
		{
			isDone = true;
		}
		return;
	}
	else if (isMove)
	{
		if (bullet_dir == 1 && ny != 0)
		{
			ani = 1;
		}
		else if (bullet_dir == -1 && ny != 0)
		{
			ani = 2;
		}
		else if(bullet_dir == 1)
		{
			ani = 3;
		}
		else if (bullet_dir == -1)
		{
			ani = 4;
		}
		else 
		{
			ani = 0;
		}
	}

	if (this->GetState() == 5)
	{
		ani = 5;
		animation_set->at(ani)->Render(x, y);
		if (animation_set->at(ani)->GetCurrentFrame() == 0)
		{
			isDone = true;
		}
		return;
	}


	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void BulletSkull::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDone)
	{
		left = x;
		top = y;
		right = x + 10;
		bottom = y + 10;
	}
}

void BulletSkull::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case 0:
		vx = 0;
		vy = 0.075f;
		nx = 0;
		ny = 1;
		break;
	case 1:
		vx = 0.505f;
		vy = -0.505f;
		nx = 1;
		ny = -1;
		break;
	case 2:
		vx = -0.505f;
		vy = -0.505f;
		nx = -1;
		ny = -1;
		break;
	case 3:
		vx = 0.205f;
		vy = 0;
		nx = 1;
		ny = 0;
		break;
	case 4:
		vx = -0.205f;
		vy = 0;
		nx = -1;
		ny = 0;
		break;
	case 5:
		vx = vy = nx = ny = 0;
		break;
	}
}
