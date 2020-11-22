#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Sophia.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"

#include "StateIDLE.h"
#include "StateTURN.h"
#include "StateFALL.h"
#include "StateJUMP.h"

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
	//vy += SOPHIA_GRAVITY*dt;
	vy += 0.001f * dt;

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
		/*y += min_ty*dy + ny*0.4f;*/

		if (nx!=0) vx = 0;
		if (ny!=0) vy = 0;


		//
		// Collision logic with other objects
		//
		
		
	}

	currentState->Update();


	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CSophia::Render()
{
	int alpha = 255;
	if (untouchable) alpha = 128;

		
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
			
	case DIK_SPACE:
		if (!isJumping && !isFalling)
		{
			isJumping = true;
			SwitchState(new StateJUMP());
			currentAni->ResetCurrentFrame();
		}
		break;
	}
}

void CSophia::OnKeyUp(int keycode)
{
}

void CSophia::KeyState()
{
}

void CSophia::SetStartPos(float startx, float starty)
{
	start_x = startx;
	start_y = starty;
}

#pragma endregion


void CSophia::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{

	if (isRaisedGun || isGunUp)
	{
		left = x;
		top = y - (SOPHIA_BIG_BBOX_HEIGHT - SOPHIA_SMALL_BBOX_HEIGHT);
		right = x + SOPHIA_BIG_BBOX_WIDTH;
		bottom = top + SOPHIA_BIG_BBOX_HEIGHT;
		
	}
	else
	{
		left = x;
		top = y;
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

