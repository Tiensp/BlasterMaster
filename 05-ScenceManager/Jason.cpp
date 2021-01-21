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
#include "StateCLIMB.h"
#include "StateOPENCabin.h"
#include "Brick.h"
#include "Ladder.h"

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
		// Simple fall down
		vy += SOPHIA_GRAVITY * dt;

		set_bullet_list();
		for (int i = 0; i < p_bullet_list.size(); i++)
		{
			p_bullet_list[i]->Update(dt, coObjects);

		}


		if (state != JASON_STATE_DIE)
		{
			if (currentState->StateName == JASON_CLIMB)
			{
				if ((this->y <= Ladder->y && this->ny == -1) || (((this->y) >= (Ladder->y + Ladder->height -JASON_BIG_BBOX_HEIGHT-5)) && this->ny == 1))
				{
					SwitchState(new StateIDLE());
				}


			}
			CheckCollisionWithLadder(coObjects);
			CheckCollisionWithBrick(coObjects);

		}

		// reset untouchable timer if untouchable time has passed
		if (GetTickCount64() - untouchable_start > JASON_UNTOUCHABLE_TIME)
		{
			untouchable_start = 0;
			untouchable = 0;
		}

		// No collision occured, proceed normally


		if (jumpIntoCabin)
		{
			CSophia* sophia = INSTANCE_SOPHIA;
			if (y + JASON_BIG_BBOX_HEIGHT >= sophia->y + SOPHIA_SMALL_BBOX_HEIGHT * 0.75)
			{
				jumpIntoCabin = false;
				_ACTIVE[JASON] = false;
				sophia->SetIsFrozen(false);
				sophia->SetIsOpenCabin(true);
				sophia->frameID = -1;
				sophia->SwitchState(new StateOPENCabin(), NORMAL_STATE);
			}

		}
		else
			currentState->Update();

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
		RenderBoundingBox(x, y);
	}
}
#pragma region Xử lý phím

void CJason::OnKeyDown(int keycode)
{
	switch (keycode)
	{
	case DIK_DOWN:
		if (isColLadder)
		{
			this->x = Ladder->x;
			this->ny = 1;
			SwitchState(new StateCLIMB());
			renderFrame = false;
			isCrawling = false;
		}
		else if (!isCrawling && !isColLadder)
		{
			SwitchState(new StateCRAWL());
			renderFrame = true;
			isCrawling = true;
		}
		break;
	case DIK_UP:
		//kiểm tra giao với cầu thang
		//nếu giao => StateClimb
		//isclimb = true
		//StateClimb
		if (isColLadder)
		{
			this->ny = -1;
			this->x = Ladder->x;
			SwitchState(new StateCLIMB());
			renderFrame = false;
			isCrawling = false;
		}
		/*	if (isCrawling)
			{
				SwitchState(new StateIDLE());
				renderFrame = false;
				isCrawling = false;
			}*/

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
	case DIK_Q:
	{
		CSophia* sophia = INSTANCE_SOPHIA;
		if (IsCollidingObject(sophia))
		{
			nx = sophia->nx;
			jumpIntoCabin = true;
			ResetAtPos(sophia->x + SOPHIA_BIG_BBOX_WIDTH / 2 - JASON_BIG_BBOX_WIDTH / 2,
				sophia->y - (SOPHIA_OPEN_CABIN_BBOX_HEIGHT - SOPHIA_SMALL_BBOX_HEIGHT)
				- JASON_BIG_BBOX_HEIGHT * 0.25);
		}
		break;
	}
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

void CJason::ResetAtPos(float _x, float _y)
{
	SetPosition(_x, _y);
	SwitchState(new StateIDLE());
	SetSpeed(0, 0);
}

void CJason::CheckCollisionWithBrick(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	bool isColideUsingAABB = false;
	coEvents.clear();

	vector<LPGAMEOBJECT> ListBrick;
	ListBrick.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (dynamic_cast<CBrick*>(coObjects->at(i)))
			ListBrick.push_back(coObjects->at(i));
	CalcPotentialCollisions(&ListBrick, coEvents);
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

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		LPCOLLISIONEVENT e = coEventsResult[0];
		if (isColLadder)
		{
			if (currentState->StateName == JASON_CLIMB)
			{
				x += dx;
				y += dy;
			}
			else if (currentState->StateName == JASON_WALKING_LEFT || currentState->StateName == JASON_WALKING_RIGHT)
			{
				x += dx;
			}
		}
		else
		{
			x += min_tx * dx + nx * 0.2f;
			y += min_ty * dy + ny * 0.2f;
			if (e->nx != 0) vx = 0;
			if (e->ny == -1)
			{
				vy = 0;
			}
			else if (e->ny == 1)
			{
				vy = 0;
			}
		}






	}


}

void CJason::CheckCollisionWithLadder(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	bool isColideUsingAABB = false;
	coEvents.clear();
	vector<LPGAMEOBJECT> ListLadder;

	ListLadder.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CLadder*>(coObjects->at(i)))
			ListLadder.push_back(coObjects->at(i));
	}


	for (int i = 0; i < ListLadder.size(); i++)
	{
		if (this->IsCollidingObject(ListLadder.at(i)))
		{
			CLadder* ladder = dynamic_cast<CLadder*>(ListLadder.at(i));
			isColideUsingAABB = true;
			Ladder = ladder;
			this->isColLadder = true;

		}
		else
		{
			this->isColLadder = false;
		}

	}

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

CJason* INSTANCE_JASON
{
	if (__instance == NULL) {
		__instance = new CJason();
	}
	return __instance;
}

