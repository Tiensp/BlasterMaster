#include "Skulls.h"
#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Sophia.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"
#include "Brick.h"
CSkull::CSkull(float x, float y, LPGAMEOBJECT player)
{
	SetState(SKULL_ANI_WALKING_LEFT);
	this->x = x;
	this->y = y;
	this->target = player;

	hp = 1;

	objTag = ENEMY;
	objType = SKULLS;

}

void CSkull::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDoneDeath)
	{
		left = x;
		top = y;
		right = x + SKULL_BBOX_WIDTH;
		bottom = y + SKULL_BBOX_HEIGHT;
	}
	else return;
}

void CSkull::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::Update(dt, coObjects);
	Attack();

	if (sk_bullet != NULL)
	{
		if (!sk_bullet->isDone)
		{
			sk_bullet->Update(dt, coObjects);
		}
		else
		{
			sk_bullet = NULL;
		}
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;

	}
	else //có va chạm
	{
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);  

		{
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<CBrick*>(e->obj))
				{
					isAttack = false;

					CBrick* brick = dynamic_cast<CBrick*>(e->obj);

					if (e->nx != 0)
					{
						if (e->nx > 0)
						{
							if (this->nx < 0)
							{
								if (this->GetState() == SKULL_ANI_WALKING_LEFT)
								{
									this->SetState(SKULL_ANI_WALKING_RIGHT);
								}
							}
						}
						else if(e->nx < 0)
						{
							if (this->nx > 0)
							{
								if (this->GetState() == SKULL_ANI_WALKING_RIGHT)
								{
									this->SetState(SKULL_ANI_WALKING_LEFT);
								}
							}
						}
					}
				}
				else {
					x += dx;
					y += dy;
				}
			}
		}
	}
}

void CSkull::Attack()
{

	if (abs(this->x - target->x) <= 5)
	{
		isAttack = true;
		if (this->GetState() == SKULL_ANI_WALKING_LEFT)
		{
			if (sk_bullet == NULL && this->nx)
			{
				sk_bullet = new BulletSkull(this->x, this->y, this->target);
				sk_bullet->SetPosition(this->x + width + 10, this->y + height + 15);
				sk_bullet->Set_bullet_dir(3);
				sk_bullet->Set_IsMove(true);
			}
			this->SetState(SKULL_ANI_ATTACKING_LEFT);
		}
		else if (this->GetState() == SKULL_ANI_WALKING_RIGHT)
		{
			if (sk_bullet == NULL && this->nx)
			{
				sk_bullet = new BulletSkull(this->x, this->y, this->target);
				//sk_bullet->SetPosition(this->x + width + 10, this->y + height + 15);
				sk_bullet->Set_bullet_dir(3);
				sk_bullet->Set_IsMove(true);
			}
			this->SetState(SKULL_ANI_ATTACKING_RIGHT);
		}
	}
	else
	{
		isAttack = false;
		if (this->nx > 0)
		{
			this->SetState(SKULL_ANI_WALKING_RIGHT);
		}
		else if (this->nx < 0)
		{
			this->SetState(SKULL_ANI_WALKING_LEFT);
		}
	}

}



void CSkull::Render()
{
	int ani = SKULL_ANI_WALKING_LEFT;

	if (isDoneDeath) return;
	if (hp <= 0) isDeath = true;

	if (isDeath)
	{
		ani = SKULL_ANI_DEATH;
		animation_set->at(ani)->Render(x, y);
		if (animation_set->at(ani)->GetCurrentFrame() == 3)
		{
			isDoneDeath = true;
		}
		return;
	}
	
	if (isAttack)
	{
		if (nx > 0)
		{
			ani = SKULL_ANI_ATTACKING_RIGHT;
		}
		else if (nx < 0)
		{
			ani = SKULL_ANI_ATTACKING_LEFT;
		}
	}
	else
	{
		if (nx > 0)
		{
			if (vx > 0)
			{
				ani = SKULL_ANI_WALKING_RIGHT;
			}
		}
		else if (nx < 0)
		{
			if (vx < 0)
			{
				ani = SKULL_ANI_WALKING_LEFT;
			}
		}
	}

	if (sk_bullet != NULL)
	{
		sk_bullet->Render();
	}

	DebugOut(L"ani: %d\n", ani);

	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox(x,y);
}


void CSkull::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SKULL_ANI_WALKING_LEFT:
		vx = -SKULL_WALKING_SPEED;
		nx = -1;
		vy = 0;
		ny = 0;
		break;
	case SKULL_ANI_WALKING_RIGHT:
		vx = SKULL_WALKING_SPEED;
		nx = 1;
		vy = 0;
		ny = 0;
		break;
	case SKULL_ANI_ATTACKING_LEFT:
		vx = 0;
		nx = -1;
		vy = 0;
		ny = 0;
		break;
	case SKULL_ANI_ATTACKING_RIGHT:
		vx = 0;
		nx = 1;
		vy = 0;
		ny = 0;
		break;
	case SKULL_ANI_COLLISION_LEFT:
		vx = -SKULL_WALKING_SPEED;
		nx = -1;
		vy = 0;
		ny = 0;
		break;
	case SKULL_ANI_COLLISION_RIGHT:
		vx = SKULL_WALKING_SPEED;
		nx = 1;
		vy = 0;
		ny = 0;
		break;
	}
}
