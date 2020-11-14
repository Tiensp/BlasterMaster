#include "Golem.h"
#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Sophia.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"
CGolem::CGolem()
{
	SetState(GOLEM_STATE_WALKING);

}

void CGolem::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + GOLEM_BBOX_WIDTH;

	if (state == GOLEM_STATE_DIE)
		bottom = y + GOLEM_BBOX_HEIGHT_DIE;
	else
		bottom = y + GOLEM_BBOX_HEIGHT;
}

void CGolem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	vy += 0.002f * dt;
	//DebugOut(L"golumnvX: %f, golumnvY: %f\n", vx, vy);

	//x += dx;
	//y += dy;

	//if (vx < 0 && x < 0) {
	//	x = 0; vx = -vx;
	//}

	//if (vx > 0 && x > 290) {
	//	x = 290; vx = -vx;
	//}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);


	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Sophia if collides with a moving objects, what if Sophia is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

	/*	if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;*/
		if (nx != 0)
		{
			this->nx = -this->nx;
			DebugOut(L"golumnvX: %f, golumnvY: %f\n", this->nx, vy);

		}
		if (ny != 0)
		{

			vy = 0;
			for (int i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult.at(i);
				if (e->ny != 0)
				{

				}
			}
		}


		//
		// Collision logic with other objects
		//
		//for (UINT i = 0; i < coEventsResult.size(); i++)
		//{
		//	LPCOLLISIONEVENT e = coEventsResult[i];

		//	if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
		//	{
		//		CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

		//		// jump on top >> kill Goomba and deflect a bit 
		//		if (e->ny < 0)
		//		{
		//			if (goomba->GetState() != GOOMBA_STATE_DIE)
		//			{
		//				goomba->SetState(GOOMBA_STATE_DIE);
		//				vy = -SOPHIA_JUMP_DEFLECT_SPEED;
		//			}
		//		}
		//		
		//		}
		//	} // if Goomba
			
		}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	}



void CGolem::Render()
{
	int ani = GOLEM_ANI_WALKING_RIGHT;
	if (vx > 0) ani = GOLEM_ANI_WALKING_RIGHT;
	else if (vx <= 0) ani = GOLEM_ANI_WALKING_LEFT;

	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
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
	}
}
