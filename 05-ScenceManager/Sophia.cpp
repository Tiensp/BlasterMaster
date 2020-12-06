#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Sophia.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"
#include "Domes.h"
#include "Camera.h"

#include "StateIDLE.h"
#include "StateTURN.h"
#include "StateFALL.h"
#include "StateJUMP.h"
#include "Brick.h"
#include <vector>
CSophia* CSophia::__instance = NULL;

CSophia::CSophia() : CGameObject()
{
	level = SOPHIA_LEVEL_BIG;
	untouchable = 0;
	animation_set = CAnimationSets::GetInstance()->Get(SOPHIA);

	start_x = x; 
	start_y = y; 
	this->x = x; 
	this->y = y; 
	y_render = y;



}

void CSophia::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (_ACTIVE[SOPHIA])
	{
		// Calculate dx, dy 
		CGameObject::Update(dt);
		
		set_bullet_list();
		

		// Simple fall down
		vy += SOPHIA_GRAVITY*dt;	
		
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		// turn off collision when die 
		if (state != SOPHIA_STATE_DIE)
			CalcPotentialCollisions(coObjects, coEvents);

		// reset untouchable timer if untouchable time has passed
		if (GetTickCount64() - untouchable_start > SOPHIA_UNTOUCHABLE_TIME)
		{
			untouchable_start = 0;
			untouchable = 0;
		}

		// No collision occured, proceed normally
		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
			isColliBrick = false;
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
			
			/*y += min_ty*dy + ny*0.4f;*/

			if (nx != 0) vx = 0;
			if (ny != 0) vy = 0;
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<CBrick*>(e->obj)) // if e->obj is Goomba 
				{
					CBrick* br = dynamic_cast<CBrick*>(e->obj);
					lastColliObj.left = br->x;
					lastColliObj.top = br->y;
					lastColliObj.right = lastColliObj.left + br->width;
					lastColliObj.bottom = lastColliObj.top + br->height;
					x += min_tx * dx + nx * 0.4f;
					y += min_ty * dy + ny * 0.4f;
					isColliBrick = true;
				}
				else if (dynamic_cast<Enemy*>(e->obj)) // if e->obj is Goomba 
				{
					x += dx;
					health -= 1;
				}
				else if (e->obj->objTag == Portal)
				{
					x += dx;
					CPortal* por = dynamic_cast<CPortal*>(e->obj);
					if (e->nx == -1 && por->nx == 1)
					{
						CCamera* camera = CCamera::GetInstance();
						camera->isSwitchScene = true;
						D3DXVECTOR2 camPos = camera->GetCamPos();
						camera->SwitchScenePos = D3DXVECTOR2(camPos.x + camera->GetWidth(), camPos.y);
					}
					else if (e->nx == 1 && por->nx == -1)
					{
						CCamera* camera = CCamera::GetInstance();
						camera->isSwitchScene = true;
						D3DXVECTOR2 camPos = camera->GetCamPos();
						camera->SwitchScenePos = D3DXVECTOR2(camPos.x - camera->GetWidth(), camPos.y);
					}
				}
			}

			//
			// Collision logic with other objects
			//


		}
		x_render = x;
		y_render = y;

		currentState->Update();

		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void CSophia::Render()
{
	
	if (_ACTIVE[SOPHIA])
	{
		int alpha = 255;
		if (untouchable) alpha = 128;

		//currentAni->Render(x, y_render);
		if (isRaisedGun || isLoweredGun)
		{
			if (currentAni->GetCurrentFrame() == currentAni->GetLastFrame() - 1)
			{
				isRaisedGun = false;
				isLoweredGun = false;
			}
		}
		if (isTurning) 
		{
			if (currentAni->IsFinalFrame())
			{
				isTurning = false;
			}
		}

		/*if (renderFrame)
			currentAni->RenderFrame(frameID, x_render, y_render);
		else*/
			currentAni->Render(x_render, y_render);
		//RenderBoundingBox();

		for (int i = 0; i < p_bullet_list.size(); i++)
		{
			BulletObject* p_bullet = p_bullet_list.at(i);
			if (p_bullet != NULL)
			{
				if (p_bullet->Get_IsMove() == true)
				{
					p_bullet->Render();
				}
			}
		}
	}
}
#pragma region Xử lý phím

void CSophia::OnKeyDown(int keycode)
{
	BulletObject* p_bullet = new BulletObject();
	switch (keycode)
	{
	case DIK_S:
		break;
			
	case DIK_SPACE:
		if (!isJumping && !isFalling)
		{
			/*if (isGunUp)
			{
				SwitchState(new StateI());
				currentAni->ResetCurrentFrame();
			}*/
			SwitchState(new StateJUMP());
			currentAni->ResetCurrentFrame();
		}
		break;
	case DIK_Z:
	{
		if (AllowFire())
		{
			p_bullet = new SophiaBullet(this->x, this->y);
			if (isGunUp == false)
			{
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
			}
			else
			{
				if (this->nx == 1)
				{
					p_bullet->SetPosition(this->x + width / 2 + 2, this->y - 20);
					p_bullet->Set_bullet_dir(3);
				}
				else
				{
					p_bullet->SetPosition(this->x + width / 2 + 10, this->y - 20);
					p_bullet->Set_bullet_dir(3);
				}

			}
			if (Get_Sophia_Normal_bullet() <= 2)
			{
				p_bullet->Set_IsMove(true);
				p_bullet_list.push_back(p_bullet);
			}
		}
		break;	
	}
	case DIK_X:
	{
		if (AllowFire() && numberThreeBullet > 0 )
		{
			p_bullet = new ThreeBullet(this->x, this->y, this->nx);
			p_bullet->Set_IsMove(true);
			isAllowFire = false;
			p_bullet_list.push_back(p_bullet);
			numberThreeBullet--;
		}
		break;
	}
	case DIK_C:
	{
		if (AllowFire() && numberThunderBullet > 0)
		{
			p_bullet = new ThunderBullet(this->x, this->y);
			p_bullet->SetPosition(this->x, this->y);
			isAllowFire = false;
			p_bullet->Set_IsMove(true);
			p_bullet_list.push_back(p_bullet);
			numberThunderBullet--;
		}
	
		break;
	}

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
		top = y - SOPHIA_BIG_BBOX_HEIGHT + SOPHIA_SMALL_BBOX_HEIGHT;
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



bool CSophia::AllowFire()
{
	for (int i = 0; i < p_bullet_list.size(); i++)
	{
		if (dynamic_cast<ThreeBullet*>(p_bullet_list[i])|| dynamic_cast<ThunderBullet*>(p_bullet_list[i]))
		{
			
			return false;
		}
	}
	return true;
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
void CSophia::Reset()
{
	SetLevel(SOPHIA_LEVEL_BIG);
	SetPosition(start_x, start_y);
	SwitchState(new StateIDLE());
	SetSpeed(0, 0);
}

void CSophia::set_bullet_list()
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

int CSophia::Get_Sophia_Normal_bullet()
{
	int count = 0;
	for (int i = 0; i < p_bullet_list.size(); i++)
	{
		if (dynamic_cast<SophiaBullet*>(p_bullet_list[i]))
		{
			count += 1;
		}
	}
	return count;
}

CSophia* CSophia::GetInstance()
{
	if (__instance == NULL) {
		__instance = new CSophia();
	}
	return __instance;
}

