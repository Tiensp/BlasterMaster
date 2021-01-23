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
#include "RockOVH.h"
#include "ThornOVERHEAD.h"
#include "BigJasonBullet.h"
#include "Camera.h"
#include "PlayScence.h"
#include "StateWALKING.h"


CBigJason* CBigJason::__instance = NULL;

CBigJason::CBigJason() : CGameObject()
{
	level = BIG_JASON_LEVEL_BIG;
	untouchable = 0;
	animation_set = CAnimationSets::GetInstance()->Get(BIG_JASON);
	isDead = false;
	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
	energy = 2;
}

void CBigJason::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<CEnemyBullet*>* listBulletBoss)
{
	if (_ACTIVE[BIG_JASON])
	{
		if (this->health <= 0)
		{
			SwitchState(new StateDead());
		}
		// Calculate dx, dy 
		CGameObject::Update(dt);
		CheckCollisionWithBrick(coObjects);
		CheckCollisionWithEnemy(coObjects);
		CheckCollisionWithItem(coObjects);
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();
		CalcPotentialCollisions(coObjects, coEvents);
		// reset untouchable timer if untouchable time has passed
	
		if (GetTickCount() - untouchable_start > BIG_JASON_UNTOUCHABLE_TIME)
		{
			if (untouchable == 1)
				isInjured = false;
			untouchable = 0;
			untouchable_start = 0;
		}
		set_bullet_list();
		for (int i = 0; i < p_bullet_list.size(); i++)
		{

			dynamic_cast<BigJasonBullet*>(p_bullet_list.at(i))->Update(dt, coObjects, listBulletBoss);
		}
		// No collision occured, proceed normally
		if (coEvents.size() == 0)
		{
			/*x += dx;
			y += dy;*/
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
			

			
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<CBrick*>(e->obj)) // if e->obj is Goomba 
				{
					if (nx != 0) vx = 0;
					if (ny != 0) vy = 0;
					x += min_tx * dx + nx * 0.4f;
					y += min_ty * dy + ny * 0.4f;
				}
				else if (dynamic_cast<CRockOVH*>(e->obj)) // if e->obj is Goomba 
				{
					
				}
				else if (dynamic_cast<CThornOVH*>(e->obj)) // if e->obj is Goomba 
				{
					x += dx;
					y += dy;
				}
				else if (dynamic_cast<CPortal*>(e->obj))
				{
					CCamera* camera = CCamera::GetInstance();
					CPortal* por = dynamic_cast<CPortal*>(e->obj);
				
					/// CHUYỂN SCENE KHI CHẠM PORTAL
					
					if (por->objType == OVHHorizontal)
					{
						camera->switchHorizontal = true;

						if (e->nx == -1 && por->nx == -1)
						{
							camera->isSwitchScene = true;
							camera->switchSceneOVHead = true;

							isAutoGo = true;
							autoGoX = true;
							autoGoDes = por->x_des + 2;
							camera->miniScene_des = por->GetDesScene();
							D3DXVECTOR2 camPos = camera->GetCamPos();
							camera->SwitchScenePos = D3DXVECTOR2(camPos.x + camera->GetWidth(), camPos.y);
							((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->currentMiniScene = por->GetDesScene();
						}
						else if (e->nx == 1 && por->nx == 1)
						{
							camera->isSwitchScene = true;
							camera->switchSceneOVHead = true;

							isAutoGo = true;
							autoGoX = true;
							autoGoDes = por->x_des - SOPHIA_BIG_BBOX_WIDTH;
							camera->miniScene_des = por->GetDesScene();
							D3DXVECTOR2 camPos = camera->GetCamPos();
							camera->SwitchScenePos = D3DXVECTOR2(camPos.x - camera->GetWidth(), camPos.y);
							((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->currentMiniScene = por->GetDesScene();
						}
					}
					else if (por->objType == OVHVerticle)
					{
						if (e->ny == -1 && por->nx == 1)
						{
							camera->isSwitchScene = true;
							camera->switchSceneOVHead = true;
							camera->switchVerticle = true;
							isAutoGo = true;
							autoGoY = true;
							autoGoDes = por->y_des + 2;
							camera->miniScene_des = por->GetDesScene();
							D3DXVECTOR2 camPos = camera->GetCamPos();
							camera->SwitchScenePos = D3DXVECTOR2(camPos.x, camPos.y + camera->GetHeight());
							((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->currentMiniScene = por->GetDesScene();
						}
						else if (e->ny == 1 && por->nx == -1)
						{
							camera->isSwitchScene = true;
							camera->switchSceneOVHead = true;
							camera->switchVerticle = true;
							isAutoGo = true;
							autoGoY = true;
							autoGoDes = por->y_des - BIG_JASON_BIG_BBOX_HEIGHT;
							camera->miniScene_des = por->GetDesScene();
							D3DXVECTOR2 camPos = camera->GetCamPos();
							camera->SwitchScenePos = D3DXVECTOR2(camPos.x, camPos.y - camera->GetHeight());
							((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->currentMiniScene = por->GetDesScene();
						}
						
					}
					x += dx;
					y += dy;
				}
				
			}

		}
		if (!isAutoGo)
			currentState->Update();
		else
			AutoGo(autoGoDes);


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

		if (isDead)
		{
			/*currentAni->Render(x, y);*/

			if (currentAni->GetCurrentFrame() == currentAni->GetLastFrame())
			{
				renderFrame = true;
			}
			if (renderFrame)
				currentAni->RenderFrame(frameID, x, y + 10);
			else
				currentAni->Render(x, y);
		}
		else
		{
			if (renderFrame)
				currentAni->RenderFrame(frameID, x, y);
			else
				currentAni->Render(x, y);
		}
	}
	for (int i = 0; i < p_bullet_list.size(); i++)
	{
		p_bullet_list[i]->Render();

	}
	RenderBoundingBox(x, y);
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
	case  DIK_Z:
	{
		BigJasonBullet* p_bullet = new BigJasonBullet();
		if (energy <= 2)
		{
			p_bullet = new BigJasonBullet(this->x, this->y, 0, 0);
			p_bullet->Set_Type(0);
		}
		else if (2 < energy && energy <= 5)
		{
			p_bullet->Set_Type(1);
			if (p_bullet_list.size() == 0)
			{
				p_bullet = new BigJasonBullet(this->x, this->y, 1, 1);
			}
			else if (p_bullet_list.size() == 1)
			{
				p_bullet = new BigJasonBullet(this->x, this->y, 1, 1);
			}
			else if (p_bullet_list.size() == 2)
			{
				p_bullet = new BigJasonBullet(this->x, this->y, 1, -1);
			}
			else if (p_bullet_list.size() == 3)
			{
				p_bullet = new BigJasonBullet(this->x, this->y, 1, 1);

			}
		}
		else if (energy > 5)
		{
			p_bullet->Set_Type(2);
			if (p_bullet_list.size() == 0)
			{
				p_bullet = new BigJasonBullet(this->x, this->y, 2, 1);
			}
			else if (p_bullet_list.size() == 1)
			{
				p_bullet = new BigJasonBullet(this->x, this->y, 2, 1);
			}
			else if (p_bullet_list.size() == 2)
			{
				p_bullet = new BigJasonBullet(this->x, this->y, 2, -1);
			}
			else if (p_bullet_list.size() == 3)
			{
				p_bullet = new BigJasonBullet(this->x, this->y, 2, 1);

			}
		}
		if (this->ny == 0)
		{
			if (this->nx == 1)
			{
				p_bullet->SetPosition(this->x + width + 20, this->y + 14);

			}
			else
			{
				p_bullet->SetPosition(this->x + width - 8, this->y + 14);
			}
			p_bullet->Set_bullet_dir(this->nx);
			p_bullet->Set_point();


		}
		else if (this->nx == 0)
		{
			if (this->ny == 1)
			{
				p_bullet->SetPosition(this->x + width + 10, this->y - 5);
				p_bullet->Set_bullet_dir(3);
			}
			else
			{
				p_bullet->SetPosition(this->x + width + 2, this->y + 25);
				p_bullet->Set_bullet_dir(4);
			}
			p_bullet->Set_point();
		}

		if (Get_BigJason_Normal_bullet() <= 3)
		{

			p_bullet->Set_IsMove(true);
			p_bullet_list.push_back(p_bullet);
		}
		break;
	}


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

void CBigJason::Clear()
{
	if (__instance != NULL)
	{
		delete __instance;
		__instance = NULL;
	}
}

void CBigJason::CheckCollisionWithBrick(vector<LPGAMEOBJECT>* coObjects)
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



	if (isColideUsingAABB != true)
	{
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
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				x += min_tx * dx + nx * 0.2f;
				y += min_ty * dy + ny * 0.2f;

				if (e->nx != 0) vx = 0;
				else if (e->ny != 0)
				{
					vy = 0;

				}
			}
		}
	}
}

void CBigJason::CheckCollisionWithThorn(vector<LPGAMEOBJECT>* coObjects)
{
	
}

void CBigJason::CheckCollisionWithEnemy(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	bool isColideUsingAABB = false;
	coEvents.clear();
	vector<LPGAMEOBJECT> ListEnemy;
	vector<LPGAMEOBJECT> ListBullet;
	ListEnemy.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Enemy*>(coObjects->at(i)) || dynamic_cast<CEnemyBullet*>(coObjects->at(i))|| dynamic_cast<CThornOVH*>(coObjects->at(i)))
			ListEnemy.push_back(coObjects->at(i));
	}
	for (int i = 0; i < ListEnemy.size(); i++)
	{
		if (this->IsCollidingObject(ListEnemy.at(i)))
		{

			isColideUsingAABB = true;
			if (untouchable == 1 || isInjured)
				continue;
			health -= 1;
			/*Sound::GetInstance()->Play("PlayerInjured", 0, 1);*/
			StartUntouchable();
			return;
		}
	}
	if (!isColideUsingAABB)
	{
		CalcPotentialCollisions(&ListEnemy, coEvents);

		if (coEvents.size() == 0)
		{
			return;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			health -= 1;
			/*isInjured = true;
			Sound::GetInstance()->Play("PlayerInjured", 0, 1);*/
		}


	}
}

void CBigJason::CheckCollisionWithItem(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	bool isColideUsingAABB = false;
	int type;
	coEvents.clear();
	vector<LPGAMEOBJECT> ListItem;
	ListItem.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CItem*>(coObjects->at(i)))
		{
			ListItem.push_back(coObjects->at(i));
		}

	}
	for (int i = 0; i < ListItem.size(); i++)
	{
		if (this->IsCollidingObject(ListItem.at(i)))
		{
			isColideUsingAABB = true;
			CItem* Item = dynamic_cast<CItem*>(ListItem.at(i));
			type = Item->GetType();
			Item->SetIsVanish();
		}
	}
	if (isColideUsingAABB != true)
	{
		CalcPotentialCollisions(&ListItem, coEvents);
		if (coEvents.size() == 0)
		{
			return;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
			LPCOLLISIONEVENT e = coEventsResult[0];
			CItem* Item = dynamic_cast<CItem*>(e->obj);
			type = Item->GetType();
		}
	}
	if (type == 0)
	{
		this->health += 1;
	}
	else if(type==4)
	{
		this->energy += 1;
	}
}

void CBigJason::Revival()
{
	this->isDead = false;
	SetPosition(this->x, this->y);
	SwitchState(new StateIDLE());
	health = 8;
	/*SetSpeed(0, 0);*/
}

void CBigJason::SetHealthWithBullet(int bulletDame)
{
	this->health -= bulletDame;
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

void CBigJason::set_bullet_list()
{
	for (int i = 0; i < p_bullet_list.size(); i++)
	{
		BulletObject* p_bullet = p_bullet_list[i];
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


int CBigJason::Get_BigJason_Normal_bullet()
{
	int count = 0;
	for (int i = 0; i < p_bullet_list.size(); i++)
	{
		if (dynamic_cast<BigJasonBullet*>(p_bullet_list[i]))
		{
			count += 1;
		}
	}
	return count;
}

void CBigJason::AutoGo(float des)
{
	if (autoGoX)
	{
		if (nx > 0)
		{
			SwitchState(new StateWALKING());
			if (x >= des)
			{
				isAutoGo = false;
				autoGoX = false;
			}
		}
		else
		{
			SwitchState(new StateWALKING());
			if (x <= des)
			{
				isAutoGo = false;
				autoGoX = false;
			}
		}
	}
	else if (autoGoY)
	{
		if (ny > 0)
		{
			SwitchState(new StateWALKING());
			if (y <= des)
			{
				isAutoGo = false;
				autoGoY = false;
			}
		}
		else
		{
			SwitchState(new StateWALKING());
			if (y >= des)
			{
				isAutoGo = false;
				autoGoY = false;
			}
		}
	}
	
}

/*
	Reset BigJason status to the beginning state of a scene
*/
void CBigJason::Reset()
{
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

