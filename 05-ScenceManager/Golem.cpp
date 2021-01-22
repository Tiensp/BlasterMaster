#include "Golem.h"
#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Sophia.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"
#include "Brick.h"
CGolem::CGolem(float x, float y, LPGAMEOBJECT player, int _typeItem)
{
	SetState(GOLEM_STATE_WALKING);
	this->x = x;
	this->y = y;
	this->target = player;
	isJumping = false;
	this->typeItem = _typeItem;
	hp = 2;

	objTag = ENEMY;
	objType = GOLEM;


}

CGolem::~CGolem()
{
}

void CGolem::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	//chua lam xong
	if (!isDeath)
	{
		left = x;
		top = y;
		right = x + GOLEM_BBOX_WIDTH;
		bottom = y + GOLEM_BBOX_HEIGHT;
	}
	
}

void CGolem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::Update(dt, coObjects);
	if (!isDeath)
	{
		vy += 0.0005f * dt;
		//DebugOut(L"golumnvX: %f, golumnvY: %f\n", vx, vy);

		if (abs(this->x - target->x) <= 300 && abs(this->y - target->y) <= 20 && isJumping == false)
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
				isJumping = true;
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

					if (dynamic_cast<CBrick*>(e->obj) || dynamic_cast<CPortal*>(e->obj)) // if e->obj is Goomba 
					{
						isJumping = false;

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
					else
					{
						x += dx;
						y += dy;
					}

					/*	if (e->obj->objTag == ENEMY)
						{
							x += dx;
							y += dy;
						}
						if (e->obj->objTag == PLAYER)
						{
							x += dx;
							y += dy;
						}*/

				}

			}
			for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		}

	}

	
}



void CGolem::Render()
{
	if (!isDeath)
	{
		int ani = GOLEM_ANI_WALKING_RIGHT;



		if (vx > 0) ani = GOLEM_ANI_WALKING_RIGHT;
		else if (vx <= 0) ani = GOLEM_ANI_WALKING_LEFT;

		//if (isDeath)
		//{
		//	ani = GOLEM_ANI_DEATH;
		//	animation_set->at(ani)->Render(x, y);
		//	if (animation_set->at(ani)->GetCurrentFrame() == 3)
		//	{
		//		isDoneDeath = true;
		//	}
		//	
		//}

		animation_set->at(ani)->Render(x, y);

		RenderBoundingBox(x, y);
	}
	
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
			vx = GOLEM_WALKING_SPEED+5.00f;
		}
		else
		{
			vx = -GOLEM_WALKING_SPEED - 5.00f;
		}
		vy = -GOLEM_JUMPING_SPEED;
		break;



	}
}