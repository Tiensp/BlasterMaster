#include "Domes.h"
#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Sophia.h"
#include "Game.h"
#include "Camera.h"
#include "Goomba.h"
#include "Portal.h"
#include "Brick.h"
CDomes::CDomes(float x, float y, LPGAMEOBJECT player)
{
	SetState(DOMES_STATE_WALKING);
	this->x = x;
	this->y = y;
	this->target = player;


}

void CDomes::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + DOMES_BBOX_WIDTH;

	if (state == DOMES_STATE_DIE)
		bottom = y + DOMES_BBOX_HEIGHT_DIE;
	else
		bottom = y + DOMES_BBOX_HEIGHT;
}

void CDomes::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	vy += 0.00025f * dt;
	//DebugOut(L"golumnvX: %f, golumnvY: %f\n", vx, vy);
	CGameObject::Update(dt, coObjects);
	//DebugOut(L"golumnvX: %f, golumnvY: %f\n", vx, vy);



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
		y -= dy;
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
			// cập nhật lại vị trí y  để tránh bị hụt xuống

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;


		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBrick*>(e->obj)) // if e->obj is Goomba 
			{
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					x += min_tx * dx + nx * 0.4f;  //cập nhật lại vị trí x
					y += min_ty * dy + ny * 0.4f;
					this->nx = 1;	
					this->ny = 1;
				}
				else if (e->ny > 0)
				{
					x += min_tx * dx + nx * 0.4f;  //cập nhật lại vị trí x
					y += min_ty * dy + ny * 0.4f;
					this->nx = -1;
					this->ny = -1;
				}
				else if (e->nx < 0)
				{
					x += min_tx * dx + nx * 0.4f;  //cập nhật lại vị trí x
					y += min_ty * dy + ny * 0.4f;
					this->nx = 1;
					this->ny = -1;	
				
				}
				else if (e->nx > 0)
				{
					this->ny = 1;
					this->nx = -1;
				}
				this->SetState(DOMES_STATE_WALKING);

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



void CDomes::Render()
{
	int ani = DOMES_ANI_WALKING_RIGHT_UP;
	if (vx > 0 && vy > 0) ani = DOMES_ANI_WALKING_RIGHT_UP;
	else if (vx > 0 && vy < 0) ani = DOMES_ANI_WALKING_LEFT_DOWN;
	else if (vx < 0 && vy > 0) ani = DOMES_ANI_WALKING_DOWN_RIGHT;
	else if (vx < 0 && vy < 0) ani = DOMES_ANI_WALKING_UP_RIGHT;

	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}

void CDomes::flowPlayer(LPGAMEOBJECT player)
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



void CDomes::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case DOMES_STATE_DIE:
		y += DOMES_BBOX_HEIGHT - DOMES_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case DOMES_STATE_WALKING:
		if (nx > 0 && ny >0 )
		{
			vx = DOMES_WALKING_SPEED;
			vy = DOMES_WALKING_SPEED;
		}
		else if(nx < 0 && ny > 0 )
		{
			vx = -DOMES_WALKING_SPEED;
			vy = DOMES_WALKING_SPEED;

		}
		else if (ny < 0 && nx > 0)
		{
			vx = DOMES_WALKING_SPEED;
			vy = 0.003f;
		}
		else if (ny < 0 && nx <0)
		{
			vx = -DOMES_WALKING_SPEED;
			vy = -0.003f;
		}
		break;

	}
}
