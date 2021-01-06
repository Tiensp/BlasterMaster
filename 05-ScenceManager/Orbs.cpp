#include "Orbs.h"
#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Sophia.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"
#include "Brick.h"
COrb::COrb(float x, float y, LPGAMEOBJECT player)
{
	SetState(ORB_ANI_WALKING_RIGHT);
	this->x = x;
	this->y = y;
	this->target = player;
	objTag = ENEMY;
	objType = ORBS;
	
	hp = 1;

}

void COrb::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDoneDeath)
	{
		left = x;
		top = y;
		right = x + ORB_BBOX_WIDTH;
		bottom = y + ORB_BBOX_HEIGHT;

		/*if (state == ORB_STATE_DIE)
			bottom = y + ORB_BBOX_HEIGHT_DIE;
		else
			bottom = y + ORB_BBOX_HEIGHT;*/
	}
	else return;
}

void COrb::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{


	CGameObject::Update(dt, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	//nếu không chết thì kiểm tra toàn bộ va chạm với các đối tượng khác
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)  //nếu không có va chạm, update bình thường
	{
		x += dx;
		y += dy;

		Attack();

	}
	else //có va chạm
	{
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);  // sắp xếp lại các sự kiện va chạm đầu tiên theo trục x, y 

		{
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<CBrick*>(e->obj)) // if e->obj is Goomba 
				{

					x += min_tx * dx + nx * 0.4f;  //cập nhật lại vị trí x
					vy += 0.0005f * dt;

					// jump on top >> kill Goomba and deflect a bit 
					if (e->nx != 0)
					{
						if (e->nx > 0)
						{
							if (nx > 0)
							{
								this->SetState(ORB_ANI_WALKING_RIGHT);
							}
							else if (nx < 0)
							{
								this->SetState(ORB_ANI_WALKING_LEFT);
							}
	
						}
						else if (e->nx < 0)
						{
							if (nx < 0)
							{
								this->SetState(ORB_ANI_WALKING_LEFT);
							}
							else if (nx > 0)
							{
								this->SetState(ORB_ANI_WALKING_RIGHT);
							}
						}

					}
					else if (e->ny != 0)
					{
						if (e->ny > 0)
						{
							if (nx < 0)
							{
								if (this->GetState() == ORB_ANI_WALKING_LEFT_DOWN)
								{
									this->SetState(ORB_ANI_WALKING_LEFT);
								}
							}
							else if (nx > 0)
							{
								if (this->GetState() == ORB_ANI_WALKING_RIGHT_DOWN)
								{
									this->SetState(ORB_ANI_WALKING_RIGHT);
								}
							}
						}
						else if (e->ny < 0)
						{
							if (nx < 0)
							{
								this->SetState(ORB_ANI_WALKING_LEFT);
							}
							else if (nx > 0)
							{
								this->SetState(ORB_ANI_WALKING_RIGHT);
							}
						}
					}
				}
				else if (e->obj->objTag == PLAYER)
				{
					isDeath = true;
					this->SetState(ORB_ANI_DEATH);
				}
				else if (e->obj->objTag == ENEMY)
				{
					x += dx;
					//y += dy;
				}
			}
		}
	}
}

void COrb::Attack()
{
	if (abs(this->x - target->x) <= 70 && abs(this->y - target->y) <= 70)
	{
		isAttack = true;
		if (this->x - target->x <= 0)
		{
			nx = 1;
		}
		else nx = -1;

		if (this->GetState() == ORB_ANI_WALKING_LEFT)
		{
			if (nx > 0)
			{
				this->SetState(ORB_ANI_WALKING_RIGHT_DOWN);
			}
			else if (nx < 0)
			{
				this->SetState(ORB_ANI_WALKING_LEFT_DOWN);
			}
		}
		else if (this->GetState() == ORB_ANI_WALKING_RIGHT)
		{
			if (nx > 0)
			{
				this->SetState(ORB_ANI_WALKING_RIGHT_DOWN);
			}
			else if (nx < 0)
			{
				this->SetState(ORB_ANI_WALKING_LEFT_DOWN);
			}
		}
	}
}

void COrb::Render()
{
	int ani = ORB_ANI_WALKING_RIGHT;

	if (isDoneDeath) return;
	if (hp == 0) isDeath = true;
	
	if (isAttack || hp == 0)
	{
		if (isDeath)
		{
			ani = ORB_ANI_DEATH;
			animation_set->at(ani)->Render(x, y);
			if (animation_set->at(ani)->GetCurrentFrame() == 3)
			{
				isDoneDeath = true;
			}
			return;
		}
	}
	else 
	{
		if (nx > 0)
		{
			if (ny > 0)
			{
				ani = ORB_ANI_WALKING_RIGHT_DOWN;
			}
			else if (ny < 0)
			{
				ani = ORB_ANI_WALKING_RIGHT_UP;
			}
			else if (ny == 0)
			{
				ani = ORB_ANI_WALKING_RIGHT;
			}
		}
		else if (nx < 0)
		{
			if (ny > 0)
			{
				ani = ORB_ANI_WALKING_LEFT_DOWN;
			}
			else if (ny < 0)
			{
				ani = ORB_ANI_WALKING_LEFT_UP;
			}
			else if (ny == 0)
			{
				ani = ORB_ANI_WALKING_LEFT;
			}
		}
	}
	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox(x,y);
}


void COrb::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ORB_STATE_DIE:
		y += ORB_BBOX_HEIGHT - ORB_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case ORB_ANI_WALKING_LEFT:
		vx = -ORB_WALKING_SPEED;
		nx = -1;
		vy = 0;
		ny = 0;
		break;
	case ORB_ANI_WALKING_RIGHT:
		vx = ORB_WALKING_SPEED;
		nx = 1;
		vy = 0;
		ny = 0;
		break;
	case ORB_ANI_WALKING_LEFT_UP:
		vx = -ORB_WALKING_SPEED;
		nx = -1;
		vy = -ORB_JUMPING_SPEED;
		ny = -1;
		break;
	case ORB_ANI_WALKING_LEFT_DOWN:
		vx = -ORB_WALKING_SPEED;
		nx = -1;
		vy = ORB_JUMPING_SPEED;
		ny = 1;
		break;
	case ORB_ANI_WALKING_RIGHT_UP:
		vx = ORB_WALKING_SPEED;
		nx = 1;
		vy = -ORB_JUMPING_SPEED;
		ny = -1;
		break;
	case ORB_ANI_WALKING_RIGHT_DOWN:
		vx = ORB_WALKING_SPEED;
		nx = 1;
		vy = ORB_JUMPING_SPEED;
		ny = 1;
		break;
	case ORB_ANI_DEATH:
		vx = 0;
		nx = 0;
		vy = 0;
		ny = 0;
		break;
	}
}
