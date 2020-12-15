#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Jason.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"

#include "StateIDLE.h"
#include "StateTURN.h"
#include "StateFALL.h"
#include "StateJUMP.h"
#include "StateCRAWL.h"
#include "Brick.h"

CJason* CJason::__instance = NULL;

CJason::CJason() : CGameObject()
{
	level = JASON_LEVEL_BIG;
	untouchable = 0;
	animation_set = CAnimationSets::GetInstance()->Get(JASON);

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;

}

void CJason::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (_ACTIVE[JASON])
	{
		// Calculate dx, dy 
		CGameObject::Update(dt);
		set_bullet_list();
		for (int i = 0; i < p_bullet_list.size(); i++)
		{
			p_bullet_list[i]->Update(dt, coObjects);

		}
		
		// Simple fall down
		vy += SOPHIA_GRAVITY * dt;
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		// turn off collision when die 
		if (state != JASON_STATE_DIE)
			CalcPotentialCollisions(coObjects, coEvents);

		// reset untouchable timer if untouchable time has passed
		if (GetTickCount64() - untouchable_start > JASON_UNTOUCHABLE_TIME)
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

			// how to push back Jason if collides with a moving objects, what if Jason is pushed this way into another object?
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

void CJason::Render()
{
	if (_ACTIVE[JASON])
	{
		int alpha = 255;
		if (untouchable) alpha = 128;

		if (renderFrame)
			currentAni->RenderFrame(frameID, x, y);
		else
			currentAni->Render(x, y);

		for (int i = 0; i < p_bullet_list.size(); i++)
		{
			p_bullet_list[i]->Render();

		}
		RenderBoundingBox(x,y);
	}
}
#pragma region Xử lý phím

void CJason::OnKeyDown(int keycode)
{
	switch (keycode)
	{
	case DIK_DOWN:
		if (!isCrawling)
		{
			SwitchState(new StateCRAWL());
			renderFrame = true;
			isCrawling = true;
		}
		break;
	case DIK_UP:
		if (isCrawling)
		{
			SwitchState(new StateIDLE());
			renderFrame = false;
			isCrawling = false;
		}
		break;
	case DIK_SPACE:

		break;
	case DIK_Z:
	{
		BulletObject* p_bullet = new BulletObject();
		p_bullet = new JasonBullet(this->x, this->y);
		if (this->nx == 1)
		{
			p_bullet->SetPosition(this->x + width + 15, this->y + height * 0.3);
			p_bullet->Set_bullet_dir(this->nx);
		}
		else
		{
			p_bullet->SetPosition(this->x + width - 15, this->y + height * 0.3);
			p_bullet->Set_bullet_dir(this->nx);
		}
		if (Get_Jason_Normal_bullet() <= 1)
		{
			p_bullet->Set_IsMove(true);
			p_bullet_list.push_back(p_bullet);
		}
	}
	break;
	}
}


void CJason::OnKeyUp(int keycode)
{
}

void CJason::KeyState()
{
}

void CJason::SetStartPos(float startx, float starty)
{
	start_x = startx;
	start_y = starty;
}

#pragma endregion


void CJason::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + JASON_BIG_BBOX_WIDTH;
	bottom = y + JASON_BIG_BBOX_HEIGHT;
}



void CJason::SwitchState(CState* state)
{
	/*
		Tại hàm này, ta sẽ thay đổi state và animation hiện tại của player sang state, ani mới
	*/
	delete currentState;
	currentState = state;
	currentAni = animation_set->at(state->StateName);
}

/*
	Reset Jason status to the beginning state of a scene
*/
void CJason::Reset()
{
	SetLevel(JASON_LEVEL_BIG);
	SetPosition(start_x, start_y);
	SwitchState(new StateIDLE());
	SetSpeed(0, 0);
}

int CJason::Get_Jason_Normal_bullet()
{
	int count = 0;
	for (int i = 0; i < p_bullet_list.size(); i++)
	{
		if (dynamic_cast<JasonBullet*>(p_bullet_list[i]))
		{
			count += 1;
		}
	}
	return count;
}

void CJason::set_bullet_list()
{
	for (int i = 0; i < p_bullet_list.size(); i++)
	{
		BulletObject* p_bullet = p_bullet_list[i];
		if (p_bullet != NULL)
		{
			if (p_bullet->isDone)
			{
				p_bullet_list.erase(p_bullet_list.begin() + i);
				if (p_bullet != NULL)
				{
					delete p_bullet;
					p_bullet = NULL;
				}

			}
		}

	}
}

CJason* CJason::GetInstance()
{
	if (__instance == NULL) {
		__instance = new CJason();
	}
	return __instance;
}

