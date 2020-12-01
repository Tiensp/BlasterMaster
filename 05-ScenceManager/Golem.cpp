#include "Golem.h"
#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Sophia.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"
#include "Brick.h"
CGolem::CGolem(float x, float y, LPGAMEOBJECT player)
{
	SetState(GOLEM_STATE_WALKING);
	this->x = x;
	this->y = y;
	this->target = player;

	objTag = ENEMY;
	objType = GOLEM;


}

CGolem::~CGolem()
{
}

void CGolem::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + GOLEM_BBOX_WIDTH;
	bottom = y + GOLEM_BBOX_HEIGHT;

	
}

void CGolem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	vy += 0.0005f * dt;
	//DebugOut(L"golumnvX: %f, golumnvY: %f\n", vx, vy);

	if (abs(this->x - target->x) <= 300 && abs(this->y - target->y) <= 20)
	{
		if (this->x - target->x <= 0)
		{
			this->nx = 1;
		}
		else
		{
			this->nx = -1;
		}
		if (abs(this->x - target->x) <= 70)
		{
			this->SetState(GOLEM_STATE_JUMPING);
		}
		else
		{
			this->SetState(GOLEM_STATE_WALKING);
		}


	}


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
		float min_tx, min_ty, nx = 0, ny=0;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);  // sắp xếp lại các sự kiện va chạm đầu tiên theo trục x, y 

		x += min_tx * dx + nx * 0.4f;  

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		
		else
		{
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<CBrick*>(e->obj)) // if e->obj is Goomba 
				{
					
				
					x += min_tx * dx + nx * 0.4f;

					if (nx != 0) vx = 0;
					if (ny != 0) vy = 0;
					CBrick* brick = dynamic_cast<CBrick*>(e->obj);

					// jump on top >> kill Goomba and deflect a bit 
					if (e->nx != 0)
					{
						this->nx = e->nx;

						this->SetState(GOLEM_STATE_WALKING);
					}

				}
			
			}

		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}



void CGolem::Render()
{
	int ani = GOLEM_ANI_WALKING_RIGHT;
	if (vx > 0) ani = GOLEM_ANI_WALKING_RIGHT;
	else if (vx <= 0) ani = GOLEM_ANI_WALKING_LEFT;

	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}

void CGolem::flowPlayer(LPGAMEOBJECT player)
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



void CGolem::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOLEM_STATE_DIE:
		y += GOLEM_BBOX_HEIGHT - GOLEM_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case GOLEM_STATE_WALKING:
		if (nx > 0)
		{
			vx = GOLEM_WALKING_SPEED;
		}
		else
		{
			vx = -GOLEM_WALKING_SPEED;
		}
		break;
	case GOLEM_STATE_JUMPING:
		if (nx > 0)
		{
			vx = GOLEM_WALKING_SPEED+0.09f;
		}
		else
		{
			vx = -GOLEM_WALKING_SPEED - 0.09f;
		}
		vy = -GOLEM_JUMPING_SPEED;
		break;


		
	}
}
