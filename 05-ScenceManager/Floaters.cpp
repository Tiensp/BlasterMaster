#include "Floaters.h"
#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Sophia.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"
#include "Brick.h"
CFloaters::CFloaters(float x, float y, LPGAMEOBJECT player)
{
	SetState(FLOATER_ANI_WALKING_LEFT_UP);
	this->x = x;
	this->y = y;
	this->target = player;

	hp = 1;

	objTag = ENEMY;
	objType = FLOATERS;

}

void CFloaters::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDoneDeath)
	{
		left = x;
		top = y;
		right = x + FLOATER_BBOX_WIDTH;
		bottom = y + FLOATER_BBOX_HEIGHT;

		/*if (state == FLOATER_STATE_DIE)
			bottom = y + FLOATER_BBOX_HEIGHT_DIE;
		else
			bottom = y + FLOATER_BBOX_HEIGHT;*/
	}
	else return;
}

void CFloaters::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

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
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);  // sắp xếp lại các sự kiện va chạm đầu tiên theo trục x, y 

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
						if (this->ny > 0)
						{
							this->SetState(FLOATER_ANI_WALKING_RIGHT_DOWN);
						}
						else if(this->ny < 0)
						{
							this->SetState(FLOATER_ANI_WALKING_RIGHT_UP);
						}
					}
					else
					{
						if(this->ny > 0)
						{
							this->SetState(FLOATER_ANI_WALKING_LEFT_DOWN);
						}
						else  if (this->ny < 0)
						{
							this->SetState(FLOATER_ANI_WALKING_LEFT_UP);
						}
					}

				}
				else if (e->ny != 0)
				{
					if (e->ny > 0)
					{
						if (this->nx > 0)
						{
							this->SetState(FLOATER_ANI_WALKING_RIGHT_DOWN);
						}
						else if (this->nx < 0)
						{
							this->SetState(FLOATER_ANI_WALKING_LEFT_DOWN);
						}
					}
					else if(e->ny < 0)
					{
						if (this->nx > 0)
						{
							this->SetState(FLOATER_ANI_WALKING_RIGHT_UP);
						}
						else if (this->nx < 0)
						{
							this->SetState(FLOATER_ANI_WALKING_LEFT_UP);
						}
					}
				}
			}
			if (e->obj->objTag == Player)
			{
				x += dx;
				y += dy;
			}
			if (e->obj->objTag == ENEMY)
			{
				x += dx;
				y += dy;
			}
		}
	}
}


void CFloaters::Attack()
{
	if (abs(this->x - target->x) <= 200)
	{
		isAttack = true;
		if (this->x - target->x < 0)
		{
			

			if (this->GetState() == FLOATER_ANI_WALKING_RIGHT_UP)
			{
				this->SetState(FLOATER_ANI_ATTACKING_RIGHT_UP);
			}
			else if (this->GetState() == FLOATER_ANI_WALKING_RIGHT_DOWN)
			{
				this->SetState(FLOATER_ANI_ATTACKING_RIGHT_DOWN);
			}
		}
		else if(this->x - target->x > 0)
		{
			
			
			if (this->GetState() == FLOATER_ANI_WALKING_LEFT_UP)
			{
				this->SetState(FLOATER_ANI_ATTACKING_LEFT_UP);
			}
			else if (this->GetState() == FLOATER_ANI_WALKING_LEFT_DOWN)
			{
				this->SetState(FLOATER_ANI_ATTACKING_LEFT_DOWN);
			}
		}
	}
	else 
	{
		isAttack = false;
	}
}



void CFloaters::Render()
{
	int ani = FLOATER_ANI_WALKING_LEFT_UP;

	if (isDoneDeath) return;
	if (hp == 0) isDeath = true;
	
	if (isAttack)
	{
		if (this->nx - target->nx == 0 && nx > 0 && this->x - target->x < 0)
		{
			if (ny > 0)
			{
				ani = FLOATER_ANI_ATTACKING_RIGHT_DOWN;
			}
			else if (ny < 0)
			{
				ani = FLOATER_ANI_ATTACKING_RIGHT_UP;
			}
		}
		else if (this->nx - target->nx == 0 && nx < 0 && this->x - target->x > 0)
		{
			if (ny > 0)
			{
				ani = FLOATER_ANI_ATTACKING_LEFT_DOWN;
			}
			else if (ny < 0)
			{
				ani = FLOATER_ANI_ATTACKING_LEFT_UP;
			}
		}
	}
	else
	{
		if (nx > 0)
		{
			if (ny > 0)
			{
				ani = FLOATER_ANI_WALKING_RIGHT_DOWN;
			}
			else if (ny < 0)
			{
				ani = FLOATER_ANI_WALKING_RIGHT_UP;
			}
		}
		else if (nx < 0)
		{
			if (ny > 0)
			{
				ani = FLOATER_ANI_WALKING_LEFT_DOWN;
			}
			else if (ny < 0)
			{
				ani = FLOATER_ANI_WALKING_LEFT_UP;
			}
		}
	}

	if (isDeath)
	{
		ani = FLOATER_ANI_DEATH;
		animation_set->at(ani)->Render(x, y);
		if (animation_set->at(ani)->GetCurrentFrame() == 3)
		{
			isDoneDeath = true;
		}
		return;
	}
	
	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void CFloaters::flowPlayer(LPGAMEOBJECT player)
{
	if (abs(this->x - player->x) <= 100)
	{
		if (this->x - player->x <= 0)
		{
			this->nx = -1;
		}
		else
		{
			this->nx = 1;
		}
	}

}



void CFloaters::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FLOATER_STATE_DIE:
		y += FLOATER_BBOX_HEIGHT - FLOATER_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case FLOATER_ANI_WALKING_LEFT_UP:
		vx = -FLOATER_WALKING_SPEED;
		nx = -1;
		vy = -FLOATER_JUMPING_SPEED;
		ny = -1;
		break;
	case FLOATER_ANI_WALKING_LEFT_DOWN:
		vx = -FLOATER_WALKING_SPEED;
		nx = -1;
		vy = FLOATER_JUMPING_SPEED;
		ny = 1;
		break;
	case FLOATER_ANI_WALKING_RIGHT_UP:
		vx = FLOATER_WALKING_SPEED;
		nx = 1;
		vy = -FLOATER_JUMPING_SPEED;
		ny = -1;
		break;
	case FLOATER_ANI_WALKING_RIGHT_DOWN:
		vx = FLOATER_WALKING_SPEED;
		nx = 1;
		vy = FLOATER_JUMPING_SPEED;
		ny = 1;
		break;
	case FLOATER_ANI_ATTACKING_LEFT_UP:
		vx = -FLOATER_WALKING_SPEED;
		nx = -1;
		vy = -FLOATER_JUMPING_SPEED;
		ny = -1;
		break;
	case FLOATER_ANI_ATTACKING_LEFT_DOWN:
		vx = -FLOATER_WALKING_SPEED;
		nx = -1;
		vy = FLOATER_JUMPING_SPEED;
		ny = 1;
		break;
	case FLOATER_ANI_ATTACKING_RIGHT_UP:
		vx = FLOATER_WALKING_SPEED;
		nx = 1;
		vy = -FLOATER_JUMPING_SPEED;
		ny = -1;
		break;
	case FLOATER_ANI_ATTACKING_RIGHT_DOWN:
		vx = FLOATER_WALKING_SPEED;
		nx = 1;
		vy = FLOATER_JUMPING_SPEED;
		ny = 1;
		break;
	}
}
