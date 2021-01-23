#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Jason.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"

#include "Orbs.h"
#include "Bomb.h"

#include "StateIDLE.h"
#include "StateTURN.h"
#include "StateFALL.h"
#include "StateJUMP.h"
#include "StateCRAWL.h"
#include "StateCLIMB.h"
#include "StateOPENCabin.h"
#include "Brick.h"
#include "Ladder.h"
#include "Sound.h"
#include "ThornOVERWORLD.h";
#include "Camera.h"
#include "Game.h"
#include "PlayScence.h"

CJason* CJason::__instance = NULL;

CJason::CJason() : CGameObject()
{
	isDead = false;
	level = JASON_LEVEL_BIG;
	untouchable = 0;
	animation_set = CAnimationSets::GetInstance()->Get(JASON);
	health = 8;
	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;

}

void CJason::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (_ACTIVE[JASON])
	{
		DWORD now = GetTickCount64();
		// Calculate dx, dy 
		CGameObject::Update(dt);
		// Simple fall down
		vy += SOPHIA_GRAVITY * dt;
		if (this->health <= 0)
		{
			SwitchState(new StateDead());
		}
		set_bullet_list();

		if (GetTickCount() - untouchable_start > SOPHIA_UNTOUCHABLE_TIME)
		{
			if (untouchable == 1)
				isInjured = false;
			untouchable = 0;
			untouchable_start = 0;
		}
		for (int i = 0; i < p_bullet_list.size(); i++)
		{
			p_bullet_list[i]->Update(dt, coObjects);

		}
		if (currentState->StateName == JASON_CLIMB)
		{
			if ((this->y <= Ladder->y && this->ny == -1) || (((this->y) >= (Ladder->y + Ladder->height - JASON_BIG_BBOX_HEIGHT - 5)) && this->ny == 1))
			{
				SwitchState(new StateIDLE());
			}
		}
		
		CheckCollisionWithPortal(coObjects);
		CheckCollisionWithLava(coObjects);
		CheckCollisionWithThornOVW(coObjects);
		CheckCollisionWithLadder(coObjects);
		CheckCollisionWithBrick(coObjects);
		CheckCollisionWithEnemy(coObjects);

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
		if (isDead)
		{
			/*currentAni->Render(x, y);*/
			
			if (currentAni->GetCurrentFrame() == currentAni->GetLastFrame())
			{
				renderFrame = true;
			}
			if (renderFrame)
				currentAni->RenderFrame(frameID, x, y+7);
			else
				currentAni->Render(x, y+7);
		}
		else
		{
			if (renderFrame)
				currentAni->RenderFrame(frameID, x, y);
			else
				currentAni->Render(x, y);
		}
		

		

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
		else if (switchOVH)
		{
			CPlayScene* curplScene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
				curplScene->GetGrid()->UnloadGrid();
			CGame::GetInstance()->SwitchScene(2);
			CPlayScene* plScene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
			plScene->currentMiniScene = porOVH->GetDesScene();
			MiniScene* miniScene = plScene->GetlistScenes().at(plScene->currentMiniScene);
			CCamera::GetInstance()->SetCamBound(miniScene->x, miniScene->y, miniScene->width, miniScene->height);
			CCamera::GetInstance()->SetPosition(D3DXVECTOR2(miniScene->x, miniScene->y));
			CBigJason::GetInstance()->ResetAtPos(porOVH->x_des, porOVH->y_des);
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
		if (isCrawling)
		{
			SwitchState(new StateIDLE());
			renderFrame = false;
			isCrawling = false;
		}

		break;
	case DIK_SPACE:
	{

	}
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
	if (!isCrawling)
	{
		left = x;
		top = y;
		right = x + JASON_BIG_BBOX_WIDTH;
		bottom = y + JASON_BIG_BBOX_HEIGHT;
	}
	else
	{
		left = x;
		top = y;
		right = left + JASON_BIG_BBOX_HEIGHT;
		bottom = top + JASON_BIG_BBOX_WIDTH;
	}
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


void CJason::CheckCollisionWithThornOVW(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	bool isColideUsingAABB = false;
	coEvents.clear();
	vector<LPGAMEOBJECT> ListThorn;
	ListThorn.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CThornOVW*>(coObjects->at(i)))
			ListThorn.push_back(coObjects->at(i));
	}


	for (int i = 0; i < ListThorn.size(); i++)
	{
		if (this->IsCollidingObject(ListThorn.at(i)))
		{
			isColideUsingAABB = true;
			if (untouchable == 1 || isInjured)
				continue;
			health -= 1;
			Sound::GetInstance()->Play("PlayerInjured", 0, 1);
			StartUntouchable();
			isInjured = true;
			return;
		}
	}
	if (!isColideUsingAABB)
	{
		CalcPotentialCollisions(&ListThorn, coEvents);

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
			isInjured = true;
			Sound::GetInstance()->Play("PlayerInjured", 0, 1);
		}


	}
}

void CJason::CheckCollisionWithLava(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	bool isColideUsingAABB = false;
	coEvents.clear();
	vector<LPGAMEOBJECT> ListLava;
	ListLava.clear();


	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CLava*>(coObjects->at(i)))
			ListLava.push_back(coObjects->at(i));
	}


	for (int i = 0; i < ListLava.size(); i++)
	{
		if (this->IsCollidingObject(ListLava.at(i)))
		{
			isColideUsingAABB = true;
			if (untouchable == 1 || isInjured)
				continue;
			health -= 1;
			Sound::GetInstance()->Play("PlayerInjured", 0, 1);
			StartUntouchable();
			isInjured = true;
			return;
		}
	}
	if (!isColideUsingAABB)
	{
		CalcPotentialCollisions(&ListLava, coEvents);

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
			isInjured = true;
			Sound::GetInstance()->Play("PlayerInjured", 0, 1);
		}


	}

}

void CJason::CheckCollisionWithPortal(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	bool isColliAABB = false;
	coEvents.clear();

	vector<LPGAMEOBJECT> ListPortal;
	ListPortal.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (dynamic_cast<CPortal*>(coObjects->at(i)))
			ListPortal.push_back(coObjects->at(i));

	for (int i = 0; i < ListPortal.size(); i++)
	{
		if (this->IsCollidingObject(ListPortal.at(i)))
		{
			CPortal* por = dynamic_cast<CPortal*>(ListPortal.at(i));
			isColliAABB = true;
			if (por->objType == ToOverHead)
			{
				this->switchOVH = true;
				porOVH = por;
			}
			else
				switchOVH = false;
		}
	}
	if (!isColliAABB)
	{
		CalcPotentialCollisions(&ListPortal, coEvents);

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
			CPortal* por = dynamic_cast<CPortal*>(e->obj);

			/// <summary>
			/// CHUYỂN SCENE KHI CHẠM PORTAL
			/// </summary>

			if (e->nx == -1 && por->nx == -1)
			{
				CCamera* camera = CCamera::GetInstance();
				camera->isSwitchScene = true;
				camera->switchSceneOVWorld = true;
				isAutoGo = true;
				autoGoDes = por->x_des + 2;
				camera->miniScene_des = por->GetDesScene();
				D3DXVECTOR2 camPos = camera->GetCamPos();
				camera->SwitchScenePos = D3DXVECTOR2(camPos.x + camera->GetWidth(), camPos.y);
				((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->currentMiniScene = por->GetDesScene();
			}
			else if (e->nx == 1 && por->nx == 1)
			{
				CCamera* camera = CCamera::GetInstance();
				camera->isSwitchScene = true;
				camera->switchSceneOVWorld = true;
				isAutoGo = true;
				autoGoDes = por->x_des - SOPHIA_BIG_BBOX_WIDTH;
				camera->miniScene_des = por->GetDesScene();
				D3DXVECTOR2 camPos = camera->GetCamPos();
				camera->SwitchScenePos = D3DXVECTOR2(camPos.x - camera->GetWidth(), camPos.y);
				((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->currentMiniScene = por->GetDesScene();
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

void CJason::CheckCollisionWithEnemy(vector<LPGAMEOBJECT>* coObjects)
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
		if (dynamic_cast<Enemy*>(coObjects->at(i)) || dynamic_cast<CEnemyBullet*>(coObjects->at(i)))
			ListEnemy.push_back(coObjects->at(i));

	}

	for (int i = 0; i < ListEnemy.size(); i++)
	{
		if (this->IsCollidingObject(ListEnemy.at(i)))
		{

			if (dynamic_cast<COrb*>(ListEnemy.at(i))) {
				COrb* orb = dynamic_cast<COrb*>(ListEnemy.at(i));
				orb->SetIsDeath(true);
			}
			if (dynamic_cast<CBomb*>(ListEnemy.at(i))) {
				CBomb* bomb = dynamic_cast<CBomb*>(ListEnemy.at(i));
				bomb->SetIsDeath(true);
			}
			isColideUsingAABB = true;
			if (untouchable == 1 || isInjured)
				continue;
			health -= 2;

			Sound::GetInstance()->Play("PlayerInjured", 0, 1);
			StartUntouchable();
			/*isInjured = true;*/
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

			health -= 2;
			/*isInjured = true;*/
			Sound::GetInstance()->Play("PlayerInjured", 0, 1);
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

CJason* CJason::GetInstance()
{
	if (__instance == NULL) {
		__instance = new CJason();
	}
	return __instance;
}

void CJason::Clear()
{
	if (__instance != NULL)
	{
		delete __instance;
		__instance = NULL;
	}
}

