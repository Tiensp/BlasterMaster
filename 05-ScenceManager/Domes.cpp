﻿#include "Domes.h"
#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Sophia.h"
#include "Game.h"
#include "Camera.h"
#include "Goomba.h"
#include "Portal.h"
#include "Brick.h"
#include "BulletFloaters.h"
CDomes::CDomes(float x, float y, float boundingHeight, float boundingWight, LPGAMEOBJECT player)
{
	SetState(DOMES_ANI_WALKING_LEFT_UP);
	this->x = x;
	this->y = y;
	this->boundingHeigt = boundingHeight;
	this->boundingWight = boundingWight;
	this->target = player;

	hp = 1;

	objTag = ENEMY;
	objType = DOMES;
}

void CDomes::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDoneDeath)
	{
		left = x;
		top = y;
		right = x + DOMES_BBOX_WIDTH;
		bottom = y + DOMES_BBOX_HEIGHT;

		/*	if (state == DOMES_STATE_START)
				bottom = y + DOMES_BBOX_HEIGHT_DIE;
			else
				bottom = y + DOMES_BBOX_HEIGHT;*/
	}
	else return;

}

void CDomes::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::Update(dt, coObjects);
	Atack();
	if (!isAtack)
	{
		Wall();
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (hp <= 0) isDeath = true;

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

			if (dynamic_cast<CBrick*>(e->obj) || dynamic_cast<CPortal*>(e->obj)) // if e->obj is Goomba 
			{
				isAtack = false;
				numberCollisionBrick++;


				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;

				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;

				CBrick* brick = dynamic_cast<CBrick*>(e->obj);

				if (e->ny != 0)
				{
					if (e->ny < 0)
					{
						if (this->GetState() == DOMES_ANI_WALKING_DOWN_RIGHT)
						{
							this->SetState(DOMES_ANI_WALKING_RIGHT_UP);
						}
						else if (this->GetState() == DOMES_ANI_WALKING_DOWN_LEFT)
						{
							this->SetState(DOMES_ANI_WALKING_LEFT_UP);

						}
						else
						{
							if (this->nx > 0)
							{
								this->SetState(DOMES_ANI_WALKING_RIGHT_UP);
							}
							else
							{
								this->SetState(DOMES_ANI_WALKING_LEFT_UP);
							}
						}

					}
					else if (e->ny > 0)
					{
						if (this->GetState() == DOMES_ANI_WALKING_UP_RIGHT)
						{
							this->SetState(DOMES_ANI_WALKING_RIGHT_DOWN);
						}
						else if (this->GetState() == DOMES_ANI_WALKING_UP_LEFT)
						{
							this->SetState(DOMES_ANI_WALKING_LEFT_DOWN);

						}
						else
						{
							if (this->nx > 0)
							{
								this->SetState(DOMES_ANI_WALKING_RIGHT_DOWN);
							}
							else
							{
								this->SetState(DOMES_ANI_WALKING_LEFT_DOWN);
							}
						}
					}
				}
				else if (e->nx != 0)
				{
					if (e->nx > 0)
					{
						if (this->GetState() == DOMES_ANI_WALKING_LEFT_UP)
						{
							this->SetState(DOMES_ANI_WALKING_UP_RIGHT);
						}
						else if (this->GetState() == DOMES_ANI_WALKING_LEFT_DOWN)
						{
							this->SetState(DOMES_ANI_WALKING_DOWN_RIGHT);
						}
						else
						{
							if (this->ny < 0)
							{
								this->SetState(DOMES_ANI_WALKING_UP_RIGHT);
							}
							else
							{
								this->SetState(DOMES_ANI_WALKING_DOWN_RIGHT);
							}
						}

					}
					else
					{
						if (this->GetState() == DOMES_ANI_WALKING_RIGHT_UP)
						{
							this->SetState(DOMES_ANI_WALKING_UP_LEFT);
						}
						else if (this->GetState() == DOMES_ANI_WALKING_RIGHT_DOWN)
						{
							this->SetState(DOMES_ANI_WALKING_DOWN_LEFT);
						}
						else
						{
							if (this->ny < 0)
							{
								this->SetState(DOMES_ANI_WALKING_DOWN_LEFT);

							}
							else
							{
								this->SetState(DOMES_ANI_WALKING_UP_LEFT);
							}
						}
					}
				}

				//lấy box của viên gạch hiện tại để xét di chuyển
				rectBrick.left = e->obj->x;
				rectBrick.right = rectBrick.left + e->obj->width;
				rectBrick.top = e->obj->y;
				rectBrick.bottom = e->obj->y + e->obj->height;
			}

			else
			{
				x += dx;
				y += dy;
			}
		}

	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}



void CDomes::Render()
{
	int ani = DOMES_ANI_WALKING_LEFT_UP;
	if (this->GetState() == DOMES_STATE_DIE)
	{
		ani = 0;
		return;
	}
	if (isDoneDeath) return;
	if (hp <= 0) isDeath = true;
	if (isAtack)
	{
		if (this->GetState() == DOMES_STATE_ATACK_NX)
		{
			if (nx > 0) ani = DOMES_ANI_WALKING_UP_RIGHT;
			else ani = DOMES_ANI_WALKING_UP_LEFT;
		}
		else if (this->GetState() == DOMES_STATE_ATACK_NY)
		{
			if (ny > 0) ani = DOMES_ANI_WALKING_RIGHT_DOWN;
			else ani = DOMES_ANI_WALKING_RIGHT_UP;
		}
	}
	else
	{
		if (vx == 0)
		{
			if (vy > 0)
			{
				if (nx > 0)
				{
					ani = DOMES_ANI_WALKING_DOWN_LEFT;
				}
				else
				{
					ani = DOMES_ANI_WALKING_DOWN_RIGHT;
				}
			}
			else
			{
				if (nx > 0)
				{
					ani = DOMES_ANI_WALKING_UP_LEFT;
				}
				else
				{
					ani = DOMES_ANI_WALKING_UP_RIGHT;
				}
			}
		}
		else if (vy == 0)
		{
			if (vx > 0)
			{
				if (ny > 0) ani = DOMES_ANI_WALKING_RIGHT_UP;
				else ani = DOMES_ANI_WALKING_RIGHT_DOWN;
			}
			else
			{
				if (ny > 0) ani = DOMES_ANI_WALKING_LEFT_UP;
				else ani = DOMES_ANI_WALKING_LEFT_DOWN;

			}
		}
	}

	if (isDeath)
	{
		ani = DOMES_ANI_DEATH;
		animation_set->at(ani)->Render(x, y);
		if (animation_set->at(ani)->GetCurrentFrame() == 3)
		{
			isDoneDeath = true;
		}
		return;
	}



	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox(x, y);
}

void CDomes::Wall()
{
	if (this->x >= rectBrick.right)
	{
		if (this->GetState() == DOMES_ANI_WALKING_RIGHT_UP) this->SetState(DOMES_ANI_WALKING_DOWN_RIGHT);
		else if (this->GetState() == DOMES_ANI_WALKING_RIGHT_DOWN) this->SetState(DOMES_ANI_WALKING_UP_RIGHT);
	}
	if (x <= rectBrick.left - DOMES_BBOX_HEIGHT)
	{
		if (this->GetState() == DOMES_ANI_WALKING_LEFT_UP) this->SetState(DOMES_ANI_WALKING_DOWN_LEFT);
		else if (this->GetState() == DOMES_ANI_WALKING_LEFT_DOWN) this->SetState(DOMES_ANI_WALKING_UP_LEFT);
	}
	if (this->y > rectBrick.bottom)
	{
		if (this->GetState() == DOMES_ANI_WALKING_DOWN_LEFT) this->SetState(DOMES_ANI_WALKING_RIGHT_DOWN);
		else if (this->GetState() == DOMES_ANI_WALKING_DOWN_RIGHT) this->SetState(DOMES_ANI_WALKING_LEFT_DOWN);
	}
	if (this->y <= rectBrick.top - DOMES_BBOX_HEIGHT)
	{
		if (this->GetState() == DOMES_ANI_WALKING_UP_RIGHT) this->SetState(DOMES_ANI_WALKING_LEFT_UP);
		else if (this->GetState() == DOMES_ANI_WALKING_UP_LEFT) this->SetState(DOMES_ANI_WALKING_RIGHT_UP);
	}
}

void CDomes::Atack()
{
	if (numberCollisionBrick >= 2)
	{
		if (vx == 0 && this->GetState() != DOMES_STATE_ATACK_NY)
		{
			if (abs(this->y - target->y) <= 10)
			{
				isAtack = true;
				this->SetState(DOMES_STATE_ATACK_NX);
				numberCollisionBrick = 0;
			}
		}
		if (vy == 0 && this->GetState() != DOMES_STATE_ATACK_NX)
		{
			if (abs(this->x - target->x) <= 10)
			{
				isAtack = true;
				this->SetState(DOMES_STATE_ATACK_NY);
				numberCollisionBrick = 0;
			}

		}
	}
}

void CDomes::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case DOMES_STATE_START:
		vx = -DOMES_WALKING_SPEED;
		vy = 0;
		ny = -1;
		nx = 1;
		break;
	case DOMES_ANI_WALKING_DOWN_LEFT:
		nx = 1;
		ny = 1;
		vx = 0;
		vy = DOMES_WALKING_SPEED;
		break;
	case DOMES_ANI_WALKING_UP_LEFT:
		nx = 1;
		ny = -1;
		vx = 0;
		vy = -DOMES_WALKING_SPEED;
		break;
	case DOMES_ANI_WALKING_DOWN_RIGHT:
		nx = -1;
		ny = 1;
		vx = 0;
		vy = DOMES_WALKING_SPEED;
		break;
	case DOMES_ANI_WALKING_UP_RIGHT:
		nx = -1;
		ny = -1;
		vx = 0;
		vy = -DOMES_WALKING_SPEED;
		break;
	case DOMES_ANI_WALKING_RIGHT_UP:
		nx = 1;
		ny = 1;
		vx = DOMES_WALKING_SPEED;
		vy = 0;
		break;
	case DOMES_ANI_WALKING_LEFT_UP:
		nx = -1;
		ny = 1;
		vx = -DOMES_WALKING_SPEED;
		vy = 0;
		break;
	case DOMES_ANI_WALKING_RIGHT_DOWN:
		nx = 1;
		ny = -1;
		vx = DOMES_WALKING_SPEED;
		vy = 0;
		break;
	case DOMES_ANI_WALKING_LEFT_DOWN:
		nx = -1;
		ny = -1;
		vx = -DOMES_WALKING_SPEED;
		vy = 0;
		break;
	case DOMES_STATE_ATACK_NX:
		vy = 0;
		if (nx < 0)
		{
			vx = 0.15f;
			nx = 1;
		}
		else
		{
			vx = -0.15f;
			nx = -1;
		}
		break;
	case DOMES_STATE_ATACK_NY:
		vx = 0;
		if (ny < 0)
		{
			vy = 0.15f;
			ny = 1;
		}
		else
		{
			vy = -0.15f;
			ny = -1;
		}
		break;
	case DOMES_ANI_DEATH:
		nx = 0;
		ny = 0;
		vx = 0;
		vy = 0;
		break;
	}
}
