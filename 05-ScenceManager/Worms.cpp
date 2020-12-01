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

}

void CWorm::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + WORM_BBOX_WIDTH;

	if (state == WORM_STATE_DIE)
		bottom = y + WORM_BBOX_HEIGHT_DIE;
	else
		bottom = y + WORM_BBOX_HEIGHT;
}

void CWorm::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	vy += 0.0005f * dt;
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

		// block every object first!
		x += min_tx * dx + nx * 0.4f;  //cập nhật lại vị trí x
		y += min_ty * dy + ny * 0.4f;	// cập nhật lại vị trí y  để tránh bị hụt xuống

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;


		//
		// Collision logic with other objects
		//
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
				this->SetState(WORM_STATE_WALKING);
			}
		}
		else
		{
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<CBrick*>(e->obj)) // if e->obj is Goomba 
				{
					CBrick* brick = dynamic_cast<CBrick*>(e->obj);

					// jump on top >> kill Goomba and deflect a bit 
					if (e->nx < 0)
					{
						this->SetState(WORM_STATE_WALKING);


					}
					else if (e->nx > 0)
					{
						this->SetState(WORM_STATE_WALKING);

					}
					this->nx = e->nx;

				}
				//	else if (e->nx != 0)
				//	{
				//		if (untouchable==0)
				//		{
				//			if (goomba->GetState()!=GOOMBA_STATE_DIE)
				//			{
				//				if (level > SOPHIA_LEVEL_SMALL)
				//				{
				//					level = SOPHIA_LEVEL_SMALL;
				//					StartUntouchable();
				//				}
				//				else 
				//					SetState(SOPHIA_STATE_DIE);
				//			}
				//		}
				//	}
				//} // if Goomba
				/*else if (dynamic_cast<CPortal *>(e->obj))
				{
					CPortal *p = dynamic_cast<CPortal *>(e->obj);
					CGame::GetInstance()->SwitchScene(p->GetSceneId());
				}*/
			}

		}
	}
}



void CWorm::Render()
{
	int ani = WORM_ANI_WALKING_RIGHT;
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
