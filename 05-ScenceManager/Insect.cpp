﻿#include "Insect.h"
#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Sophia.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"
#include "Brick.h"
CInsect::CInsect(float x, float y, LPGAMEOBJECT player)
{
	SetState(INSECT_ANI_WALKING_LEFT_UP);
	this->x = x;
	this->y = y;
	this->target = player;

}

void CInsect::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + INSECT_BBOX_WIDTH;

	if (state == INSECT_STATE_DIE)
		bottom = y + INSECT_BBOX_HEIGHT_DIE;
	else
		bottom = y + INSECT_BBOX_HEIGHT;
}

void CInsect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	//DebugOut(L"golumnvX: %f, golumnvY: %f\n", vx, vy);
	CGameObject::Update(dt, coObjects);
	//DebugOut(L"golumnvX: %f, golumnvY: %f\n", vx, vy);

	//DebugOut(L"golumnvX: %f, golumnvY: %f\n", target->nx, this->nx);


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

		DWORD dt = GetTickCount();

		timer += interval;

		if (timer == timeChangeState)
		{
			if (this->GetState() == INSECT_ANI_WALKING_LEFT_DOWN)
			{
				this->SetState(INSECT_ANI_WALKING_LEFT_UP);
				timer = 0;
			}
			else if (this->GetState() == INSECT_ANI_WALKING_LEFT_UP)
			{
				this->SetState(INSECT_ANI_WALKING_LEFT_DOWN);
				timer = 0;
			}
			else if (this->GetState() == INSECT_ANI_WALKING_RIGHT_DOWN)
			{
				this->SetState(INSECT_ANI_WALKING_RIGHT_UP);
				timer = 0;
			}
			else if (this->GetState() == INSECT_ANI_WALKING_RIGHT_UP)
			{
				this->SetState(INSECT_ANI_WALKING_RIGHT_UP);
				timer = 0;
			}
		}


	
	}
	else //có va chạm
	{
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);  // sắp xếp lại các sự kiện va chạm đầu tiên theo trục x, y 

		// how to push back Sophia if collides with a moving objects, what if Sophia is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 


		x += min_tx * dx + nx * 0.4f;  //cập nhật lại vị trí x
		y += min_ty * dy + ny * 0.4f;	// cập nhật lại vị trí y  để tránh bị hụt xuống

		// block every object first!
		{
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<CBrick*>(e->obj)) // if e->obj is Goomba 
				{

					CBrick* brick = dynamic_cast<CBrick*>(e->obj);

					// jump on top >> kill Goomba and deflect a bit 
					if (e->nx != 0)
					{
						if (e->nx > 0)
						{
							if (this->ny > 0)
							{
								this->SetState(INSECT_ANI_WALKING_RIGHT_DOWN);
							}
							else if (this->ny < 0)
							{
								this->SetState(INSECT_ANI_WALKING_RIGHT_UP);
							}
						}
						else if (e->nx < 0)
						{
							if (this->ny > 0)
							{
								this->SetState(INSECT_ANI_WALKING_LEFT_DOWN);
							}
							else if (this->ny < 0)
							{
								this->SetState(INSECT_ANI_WALKING_LEFT_UP);
							}
						}

					}
					else if (e->ny != 0)
					{
						if (e->ny > 0)
						{
							if (this->nx > 0)
							{
								this->SetState(INSECT_ANI_WALKING_RIGHT_DOWN);
							}
							else if (this->nx < 0)
							{
								this->SetState(INSECT_ANI_WALKING_LEFT_DOWN);
							}
						}
						else if (e->ny < 0)
						{
							if (this->nx > 0)
							{
								this->SetState(INSECT_ANI_WALKING_RIGHT_UP);
							}
							else if (this->nx < 0)
							{
								this->SetState(INSECT_ANI_WALKING_LEFT_UP);
							}
						}
					}
				}
			}
		}



	}
}

void CInsect::Render()
{
	int ani = INSECT_ANI_WALKING_LEFT_UP;

	if (vx > 0 && vy > 0)
	{
		ani = INSECT_ANI_WALKING_RIGHT_DOWN;
	}
	else if (vx > 0 && vy < 0)
	{
		ani = INSECT_ANI_WALKING_RIGHT_UP;
	}
	else if (vx < 0 && vy > 0)
	{
		ani = INSECT_ANI_WALKING_LEFT_DOWN;
	}
	else if (vx < 0 && vy < 0)
	{
		ani = INSECT_ANI_WALKING_LEFT_UP;
	}

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



void CInsect::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case INSECT_STATE_DIE:
		y += INSECT_BBOX_HEIGHT - INSECT_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case INSECT_ANI_WALKING_RIGHT_UP:
		vx = INSECT_WALKING_SPEED;
		nx = 1;
		vy = -INSECT_JUMPING_SPEED;
		ny = -1;
		break;
	case INSECT_ANI_WALKING_RIGHT_DOWN:
		vx = INSECT_WALKING_SPEED;
		nx = 1;
		vy = INSECT_JUMPING_SPEED;
		ny = 1;
		break;
	case INSECT_ANI_WALKING_LEFT_UP:
		vx = -INSECT_WALKING_SPEED;
		nx = -1;
		vy = -INSECT_JUMPING_SPEED;
		ny = -1;
		break;
	case INSECT_ANI_WALKING_LEFT_DOWN:
		vx = -INSECT_WALKING_SPEED;
		nx = -1;
		vy = INSECT_JUMPING_SPEED;
		ny = 1;
		break;
	}
}
