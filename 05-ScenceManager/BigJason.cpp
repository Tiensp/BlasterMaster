#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "BigJason.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"

#include "StateIDLE.h"
#include "StateTURN.h"
#include "StateFALL.h"
#include "StateJUMP.h"
#include "Brick.h"

CBigJason* CBigJason::__instance = NULL;

CBigJason::CBigJason() : CGameObject()
{
	level = BIG_JASON_LEVEL_BIG;
	untouchable = 0;
	animation_set = CAnimationSets::GetInstance()->Get(BIG_JASON);

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;

}

void CBigJason::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (_ACTIVE[BIG_JASON])
	{
		// Calculate dx, dy 
		CGameObject::Update(dt);


		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		// turn off collision when die 
		if (state != BIG_JASON_STATE_DIE)
			CalcPotentialCollisions(coObjects, coEvents);

		// reset untouchable timer if untouchable time has passed
		if (GetTickCount64() - untouchable_start > BIG_JASON_UNTOUCHABLE_TIME)
		{
			untouchable_start = 0;
			untouchable = 0;
		}

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

			// how to push back BigJason if collides with a moving objects, what if BigJason is pushed this way into another object?
			//if (rdx != 0 && rdx!=dx)
			//	x += nx*abs(rdx); 

			// block every object first!
			x += min_tx * dx + nx * 0.4f;
			/*y += min_ty*dy + ny*0.4f;*/

			if (nx != 0) vx = 0;
			if (ny != 0) vy = 0;
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<CBrick*>(e->obj)) // if e->obj is Goomba 
				{
					y += min_ty * dy + ny * 0.4f;
				}
			}

			//
			// Collision logic with other objects
			//


		}

		currentState->Update();


		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void CBigJason::Render()
{
	if (_ACTIVE[BIG_JASON])
	{
		int alpha = 255;
		if (untouchable) alpha = 128;


		currentAni->Render(x, y);
		//RenderBoundingBox();
	}
}
#pragma region Xử lý phím

void CBigJason::OnKeyDown(int keycode)
{
	switch (keycode)
	{
	case DIK_S:
		break;

	case DIK_SPACE:

		break;
	}
}

void CBigJason::OnKeyUp(int keycode)
{
}

void CBigJason::KeyState()
{
}

void CBigJason::SetStartPos(float startx, float starty)
{
	start_x = startx;
	start_y = starty;
}

#pragma endregion


void CBigJason::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
		left = x;
		top = y;
		right = x + BIG_JASON_BIG_BBOX_WIDTH;
		bottom = y + BIG_JASON_BIG_BBOX_HEIGHT;
}



void CBigJason::SwitchState(CState* state)
{
	/*
		Tại hàm này, ta sẽ thay đổi state và animation hiện tại của player sang state, ani mới
	*/
	delete currentState;
	currentState = state;
	currentAni = animation_set->at(state->StateName);
}

/*
	Reset BigJason status to the beginning state of a scene
*/
void CBigJason::Reset()
{
	SetLevel(BIG_JASON_LEVEL_BIG);
	SetPosition(start_x, start_y);
	SwitchState(new StateIDLE());
	SetSpeed(0, 0);
}

CBigJason* CBigJason::GetInstance()
{
	if (__instance == NULL) {
		__instance = new CBigJason();
	}
	return __instance;
}

