#include "Worms.h"
#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Sophia.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"
#include "Brick.h"
CWorm::CWorm(float x, float y, LPGAMEOBJECT player)
{
	SetState(WORM_STATE_WALKING);
	this->x = x;
	this->y = y;
	this->target = player;

	hp = 1;

	objTag = ENEMY;
	objType = WORMS;

}

void CWorm::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDoneDeath)
	{
		left = x;
		top = y;
		right = x + WORM_BBOX_WIDTH;
		bottom = y + WORM_BBOX_HEIGHT;

	}
	else return;

	/*if (state == WORM_STATE_DIE)
		bottom = y + WORM_BBOX_HEIGHT_DIE;
	else
		bottom = y + WORM_BBOX_HEIGHT;*/
}

void CWorm::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
		
		this->SetState(WORM_STATE_WALKING);
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
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);  // sắp xếp lại các sự kiện va chạm đầu tiên theo trục x, y 

		//x += min_tx * dx + nx * 0.4f;  

		//if (nx != 0) vx = 0;
		//if (ny != 0) vy = 0;

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

						this->SetState(WORM_STATE_WALKING);
					}

				}

				if (e->obj->objTag == ENEMY)
				{
					x += dx;
					//y += dy;
				}
				if (e->obj->objTag == PLAYER)
				{
					x += dx;
					//y += dy;
				}

			}

		}
		//for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}



void CWorm::Render()
{

	int ani = WORM_ANI_WALKING_RIGHT;

	if (isDoneDeath) return;
	if (hp == 0) isDeath = true;

	if (isDeath)
	{
		ani = WORM_ANI_DEATH;
		animation_set->at(ani)->Render(x, y);
		if (animation_set->at(ani)->GetCurrentFrame() == 3)
		{
			isDoneDeath = true;
		}
		return;
	}


	if (vx > 0) ani = WORM_ANI_WALKING_RIGHT;
	else if (vx <= 0) ani = WORM_ANI_WALKING_LEFT;

	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox(x,y);
}

void CWorm::flowPlayer(LPGAMEOBJECT player)
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



void CWorm::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case WORM_STATE_DIE:
		y += WORM_BBOX_HEIGHT - WORM_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case WORM_STATE_WALKING:
		if (nx > 0)
		{
			vx = WORM_WALKING_SPEED;
		}
		else
		{
			vx = -WORM_WALKING_SPEED;
		}
		break;
	}
}
