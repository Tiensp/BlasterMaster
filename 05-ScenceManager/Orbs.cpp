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
	hp = 2;

}

void COrb::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDeath)
	{
		left = x;
		top = y;
		right = x + ORB_BBOX_WIDTH;

		if (state == ORB_STATE_DIE)
			bottom = y + ORB_BBOX_HEIGHT_DIE;
		else
			bottom = y + ORB_BBOX_HEIGHT;
	}

}

void COrb::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{


	CGameObject::Update(dt, coObjects);
	if (isDone) return;
	if (hp <= 0) isDeath = true;
	if (isDeath) return;
	Attack();

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

		{
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<CBrick*>(e->obj)) // if e->obj is Goomba 
				{
					
					x += min_tx * dx + nx * 0.4f;  //cập nhật lại vị trí x
					y += min_ty * dy + ny * 0.4f;
					if (nx != 0) vx = 0;
					if (ny != 0) vy = 0;// cập nhật lại vị trí y  để tránh bị hụt xuống
					isAttack = false;

					CBrick* brick = dynamic_cast<CBrick*>(e->obj);

					// jump on top >> kill Goomba and deflect a bit 
					if (e->nx != 0)
					{
						if (e->nx > 0)
						{
							this->SetState(ORB_ANI_WALKING_RIGHT);
	
						}
						else if (e->nx < 0)
						{
							this->SetState(ORB_ANI_WALKING_LEFT);
						}

					}
					else if (e->ny != 0)
					{
						if (e->ny > 0)
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
			}
		}



	}
}

void COrb::Attack()
{
	if (abs(this->x - target->x) <= 70 && abs(this->y - target->y) <= 70)
	{
		if (this->GetState() == ORB_ANI_WALKING_LEFT)
		{
			this->SetState(ORB_ANI_WALKING_LEFT_DOWN);
		}
		if (abs(this->x - target->x) <= 15 && abs(this->y - target->y) <= 15)
		{
			isAttack = true;
			if (this->GetState() == ORB_ANI_WALKING_LEFT_DOWN)
			{
				this->SetState(ORB_ANI_ATTACKING_LEFT);
			}
		}
		else if (this->GetState() == ORB_ANI_WALKING_RIGHT)
		{
			
		}
	}
	else 
	{
		isAttack = false;
		
	}
}



void COrb::Render()
{
	int ani = ORB_ANI_WALKING_RIGHT;
	if (isDone) return;
	if (isDeath)
	{
		isDone = true;
	}
	
	if (isAttack)
	{
		if (nx > 0)
		{
			ani = ORB_ANI_ATTACKING_RIGHT;
		}
		else if (nx < 0)
		{
			ani = ORB_ANI_ATTACKING_LEFT;
		}
	}
	else 
	{
		if (vx > 0)
		{
			ani = ORB_ANI_WALKING_RIGHT;
		}
		else if (vx < 0)
		{
			ani = ORB_ANI_WALKING_LEFT;
		}
		else if (vx > 0 && vy > 0)
		{
			ani = ORB_ANI_WALKING_RIGHT_DOWN;
		}
		else if (vx < 0 && vy > 0)
		{
			ani = ORB_ANI_WALKING_LEFT_DOWN;
		}
		else if (vx > 0 && vy < 0)
		{
			ani = ORB_ANI_WALKING_RIGHT_UP;
		}
		else if (vx < 0 && vy < 0)
		{
			ani = ORB_ANI_WALKING_LEFT_UP;
		}
	}


	DebugOut(L"ani: %d\n", ani);
	DebugOut(L"attack: %d\n", isAttack);

	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}

//void CSkull::flowPlayer(LPGAMEOBJECT player)
//{
//	if (abs(this->x - player->x) <= 100)
//	{
//		if (this->x - player->x <= 0)
//		{
//			this->nx = -1;
//		}
//		else
//		{
//			this->nx = 1;
//		}
//	}
//
//}



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
	case ORB_ANI_ATTACKING_LEFT:
		vx = 0;
		nx = -1;
		vy = 0;
		ny = 0;
	case ORB_ANI_ATTACKING_RIGHT:
		vx = 0;
		nx = 1;
		vy = 0;
		ny = 0;
		break;
	}
}
