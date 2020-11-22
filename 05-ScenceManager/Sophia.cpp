#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Sophia.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"

#include "StateIDLE.h"
#include "StateTURN.h"

CSophia* CSophia::__instance = NULL;

CSophia::CSophia() : CGameObject()
{
	level = SOPHIA_LEVEL_BIG;
	untouchable = 0;
	_ACTIVE[SOPHIA] = true;
	animation_set = CAnimationSets::GetInstance()->Get(SOPHIA);

	start_x = x; 
	start_y = y; 
	this->x = x; 
	this->y = y; 
	DoneTurn = false;
	DoneGunDown = false;
	DoneGunUp = false;

}

void CSophia::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += SOPHIA_GRAVITY*dt;
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state!=SOPHIA_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > SOPHIA_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size()==0)
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
		x += min_tx*dx + nx*0.4f;
		y += min_ty*dy + ny*0.4f;

		if (nx!=0) vx = 0;
		if (ny!=0) vy = 0;


		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState()!= GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -SOPHIA_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					if (untouchable==0)
					{
						if (goomba->GetState()!=GOOMBA_STATE_DIE)
						{
							if (level > SOPHIA_LEVEL_SMALL)
							{
								level = SOPHIA_LEVEL_SMALL;
								StartUntouchable();
							}
							//else 
								//SetState(SOPHIA_STATE_DIE);
						}
					}
				}
			} // if Goomba
			else if (dynamic_cast<CPortal *>(e->obj))
			{
				CPortal *p = dynamic_cast<CPortal *>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
		}
	}
	currentState->Update();
	//Đặt lại biến DoneGunUp nếu không còn GUN UP
	if (state != SOPHIA_STATE_GUN_UP)
		DoneGunUp = false;

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CSophia::Render()
{
	int alpha = 255;
	if (untouchable) alpha = 128;
/*
	/// <summary>
	/// Set Animation based on State
	/// </summary>
	int ani = -1;
	if (state == SOPHIA_STATE_DIE)
	{
		ani = SOPHIA_ANI_DIE;
	}
	else if (state == SOPHIA_STATE_GUN_UP)
	{
		//Render ani GUN UP nếu trước đó chưa render xong ani GUN UP
		if (DoneGunUp == false)
		{
			if (lifeTimeGunUp == 0)
				lifeTimeGunUp = GetTickCount64();

			if (nx > 0)
				ani = SOPHIA_ANI_GUN_UP_RIGHT;
			else
				ani = SOPHIA_ANI_GUN_UP_LEFT;

			//Ngăn không cho render ani khác khi ani hiện tại chưa render đủ thời gian
			if (GetTickCount64() - lifeTimeGunUp >= animation_set->at(ani)->GetAniTime())
			{
				lifeTimeGunUp = 0;		//Reset lifeTimeGunUp

				if (nx > 0)
					ani = SOPHIA_ANI_IDLE_GUN_UP_RIGHT;
				else
					ani = SOPHIA_ANI_IDLE_GUN_UP_LEFT;

				DoneGunUp = true;
			}
		}
		else
		{
			//Render ani IDLE GUN UP 
			if (nx > 0)
				ani = SOPHIA_ANI_IDLE_GUN_UP_RIGHT;
			else
				ani = SOPHIA_ANI_IDLE_GUN_UP_LEFT;
		}

	}
	else if (state == SOPHIA_STATE_JUMP)
	{
		if (lifeTimeJump == 0)
			lifeTimeJump = GetTickCount64();

		if (nx > 0)
			ani = SOPHIA_ANI_JUMP_RIGHT;
		else
			ani = SOPHIA_ANI_JUMP_LEFT;

		//Ngăn không cho render ani khác khi ani hiện tại chưa render đủ thời gian
		if (GetTickCount64() - lifeTimeJump >= animation_set->at(ani)->GetAniTime())
		{
			lifeTimeJump = 0;		//Reset lifeTimeJump

			if (nx > 0)
				ani = SOPHIA_ANI_JUMP_RIGHT;
			else
				ani = SOPHIA_ANI_JUMP_LEFT;

		}
	}
	else if (level == SOPHIA_LEVEL_BIG)
	{
		//Reset lifeTimeGunUp nếu chuyển trạng thái khác nhưng chưa reset time
		lifeTimeGunUp = 0;
		//GUN DOWN
		if (raisedGun)		//Render ani GUN DOWN nếu trước đó trạng thái đang là GUN UP
		{
				if (lifeTimeGunDown == 0)
					lifeTimeGunDown = GetTickCount64();

				if (nx > 0)
					ani = SOPHIA_ANI_GUN_DOWN_RIGHT;
				else
					ani = SOPHIA_ANI_GUN_DOWN_LEFT;

				//Ngăn không cho render ani khác khi ani hiện tại chưa render đủ thời gian
				if (GetTickCount64() - lifeTimeGunDown >= animation_set->at(ani)->GetAniTime())
				{
					lifeTimeGunDown = 0;		//Reset lifeTimeGunDown
					
					if (nx > 0)
						ani = SOPHIA_IDLE_RIGHT;
					else
						ani = SOPHIA_IDLE_LEFT;

					raisedGun = false;
				}
		}
		//TURN
		else if (isTurning)
		{
			if (lifeTimeTurn == 0)
				lifeTimeTurn = GetTickCount64();

			if (nx > 0)
				ani = SOPHIA_ANI_TURN_RIGHT;
			else
				ani = SOPHIA_ANI_TURN_LEFT;

			if (GetTickCount64() - lifeTimeTurn >= animation_set->at(ani)->GetAniTime())
			{
				lifeTimeTurn = 0;		//Reset lifeTimeTurn

				if (vx == 0)
				{
					if (nx > 0) ani = SOPHIA_IDLE_RIGHT;
					else ani = SOPHIA_IDLE_LEFT;
				}
				else if (vx > 0)
					ani = SOPHIA_ANI_WALKING_RIGHT;
				else ani = SOPHIA_ANI_WALKING_LEFT;

				isTurning = false;
			}
			
		}
		//IDLE
		else
		{ 
			if (vx == 0)
			{
				if (nx > 0) ani = SOPHIA_IDLE_RIGHT;
				else ani = SOPHIA_IDLE_LEFT;
			}
			else if (vx > 0)
				ani = SOPHIA_ANI_WALKING_RIGHT;
			else ani = SOPHIA_ANI_WALKING_LEFT;

		}
	}
	



	animation_set->at(ani)->Render(x, y, alpha);

	RenderBoundingBox();*/
		
	if (isTurning || isRaisedGun || isLoweredGun)
	{
		if (currentAni->IsFinalFrame())
		{
			isTurning = false;
			isRaisedGun = false;
			isLoweredGun = false;
		}
	}

	currentAni->Render(x, y);
	RenderBoundingBox();

}
#pragma region Xử lý phím

void CSophia::OnKeyDown(int keycode)
{
	switch (keycode)
	{
	case DIK_S:
		break;
	}
}

void CSophia::OnKeyUp(int keycode)
{
}

void CSophia::KeyState()
{
}

#pragma endregion


void CSophia::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y; 

	if (level==SOPHIA_LEVEL_BIG)
	{
		right = x + SOPHIA_BIG_BBOX_WIDTH;
		bottom = y + SOPHIA_BIG_BBOX_HEIGHT;
	}
	else
	{
		right = x + SOPHIA_SMALL_BBOX_WIDTH;
		bottom = y + SOPHIA_SMALL_BBOX_HEIGHT;
	}
}



void CSophia::SwitchState(CState* state)
{
	/*
		Tại hàm này, ta sẽ thay đổi state và animation hiện tại của player sang state, ani mới
	*/
	delete currentState;
	currentState = state;
	currentAni = animation_set->at(state->StateName);
}

/*
	Reset Sophia status to the beginning state of a scene
*/
void CSophia::Reset(float _startx, float _starty)
{
	start_x = _startx;
	start_y = _starty;
	SetLevel(SOPHIA_LEVEL_BIG);
	SetPosition(start_x, start_y);
	SwitchState(new StateIDLE());
	SetSpeed(0, 0);
}

CSophia* CSophia::GetInstance()
{
	if (__instance == NULL) {
		__instance = new CSophia();
	}
	return __instance;
}

