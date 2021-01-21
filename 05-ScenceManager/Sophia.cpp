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
#include "StateWALKING.h"
#include "StateTURN.h"
#include "StateFALL.h"
#include "StateJUMP.h"
#include "StateOPENCabin.h"
#include "Brick.h"
#include "Lava.h"
#include "ThornOVERHEAD.h"
#include "ThornOVERWORLD.h"
#include <vector>
#include "PlayScence.h"
#include "StateJUMPGunUP.h"

#include "EnemyBullet.h"
#include "Sound.h"
CSophia* CSophia::__instance = NULL;

CSophia::CSophia() : CGameObject()
{
	level = SOPHIA_LEVEL_BIG;
	untouchable = 0;
	energy = 0;
	health = 8;
	animation_set = CAnimationSets::GetInstance()->Get(SOPHIA);

	start_x = x; 
	start_y = y; 
	this->x = x; 
	this->y = y; 
	y_render = y;

	objTag = PLAYER;
	objType = SOPHIA;

}

void CSophia::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (_ACTIVE[SOPHIA] && !isFrozen)
	{
		DWORD now = GetTickCount64();
		CGameObject::Update(dt);

		vy += SOPHIA_GRAVITY * dt;
	
		if (isSetFollowBullet)
		{
			BulletObject* p_bullet = new BulletObject();
			p_bullet = new FollowBullets(this->x, this->y, coObjects);
			p_bullet->SetPosition(this->x, this->y);
			p_bullet->Set_IsMove(true);
			p_bullet_list.push_back(p_bullet);
			isSetFollowBullet = false;    
		}
		set_bullet_list();
		for (int i = 0; i < p_bullet_list.size(); i++)
		{
			p_bullet_list[i]->Update(dt, coObjects);
		}
		
		if (GetTickCount() - untouchable_start > SOPHIA_UNTOUCHABLE_TIME)
		{
			if (untouchable == 1)
				isInjured = false;
			untouchable = 0;
			untouchable_start = 0;
		}
		CheckCollisionWithBrick(coObjects);
		CheckCollisionWithPortal(coObjects);
		CheckCollisionWithItem(coObjects);
		CheckCollisionWithEnemy(coObjects);
	}
	/// <summary>
	/// Check Nhân vật có đang chạm gạch hay không
	/// </summary>
	GetBoundingBox(rectL, rectT, rectR, rectB);
	if (lastColliBrick_y == NULL)
	{
		// Túc khởi tạo thì chưa chạm gạch lần nào nên biến này sẽ == NULL
		isColliBrick = false;
	}
	else if (lastColliBrick_y - rectB <= 0.5f  && rectB <= lastColliBrick_y)
	{
		// Vì code xử lý SweptAABB đẩy nhân vật lên 0.4f nên hầu như lúc nào nhân vật cũng 
		// trong trạng thái không va chạm => cần check tọa độ để biết có va chạm với gạch không
		isColliBrick = true;
	}
	else
		isColliBrick = false;
	// Cập nhật x_render, y_render
	x_render = x;
	y_render = y;

	// Nếu không phải AutoGo thì cập nhật state bình thường 
	if (!isAutoGo)
		currentState->Update();
	else
		AutoGo(autoGoDes);
	DebugOut(L"Van toc: %d\n", vx);
}

void CSophia::Render()
{
	if (_ACTIVE[SOPHIA] && !isFrozen)
	{
		int alpha = 255;
		if (untouchable) alpha = 128;

		/// CHECK OPEN CABIN: Nếu không open cabin thì không chạy code bên dưới mà return
		if (isOpenCabin)
		{
			RenderOPENCabinAni();
			RenderBoundingBox(x, y_render);
			return;
		}

		if (isRaisedGun || isLoweredGun)
		{
			// Nếu đang giương súng hoặc hạ súng thì kiểm tra xem 
			// currFR = bao nhiêu? để đặt lại biến về false
			if (currentAni->GetCurrentFrame() == currentAni->GetLastFrame() - 1)
			{
				isRaisedGun = false;
				isLoweredGun = false;
			}
		}
		if (isTurning)
		{
			// Tương tự với giương và hạ súng 
			if (currentAni->IsFinalFrame())
			{
				isTurning = false;
			}
		}
		/// <summary>
		/// CODE RENDER ANIMATION (RENDER COLOR hoặc NORMAL RENDER) 
		/// </summary>
		if (renderFrame)
		{
			/*if (changeStateType == WALK2IDLE)
			{
				frameID = wheelID;
			}*/
			if (!isInjured)
			{
				currentAni->RenderFrame(frameID, x_render, y_render);
			}
			else
			{
				currentAni->RenderFrame(frameID, x_render, y_render, GetRENDERColor());
			}
		}
		else
		{
			if (!isInjured)
			{
				currentAni->Render(x_render, y_render);
			}
			else
			{
				currentAni->Render(x_render, y_render, GetRENDERColor());
			}
		}
		RenderBoundingBox(x_render, y_render);

		/// <summary>
		/// CODE RENDER ĐẠN
		/// </summary>
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
		// Get WheelID

	}
	else if (_ACTIVE[SOPHIA] && isFrozen)
	{
		RenderOPENCabinAni();
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
		if (isColliBrick)
		{
			if (!isGunUp)
			{
				SwitchState(new StateJUMP(), NORMAL_STATE);
				currentAni->ResetCurrentFrame();
			}
			else
			{
				SwitchState(new StateJUMPGunUP(), NORMAL_STATE);
				currentAni->ResetCurrentFrame();
			}
			Sound::GetInstance()->Play("PlayerJump", 0, 1);
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
				Sound::GetInstance()->Play("PlayerFireUnderWorld", 0, 1);
			}
		}
		break;	
	}
	case DIK_X:
	{
		if (AllowFire() && numberThreeBullet > 0 )
		{
			p_bullet = new ThreeBullet(this->x, this->y, this->nx);
			p_bullet->SetPosition(this->x, this->y);
			p_bullet->Set_IsMove(true);
			isAllowFire = false;
			p_bullet_list.push_back(p_bullet);
			Sound::GetInstance()->Play("PlayerInjured", 0, 1);
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
			Sound::GetInstance()->Play("Thunder", 0, 1);
			numberThunderBullet--;
		}
		break;
	}
	case DIK_V:
	{
	
		if (numberFollowBullet > 0)
		{
			isSetFollowBullet = true;
			numberFollowBullet--;
		}
	
		break;
	}
	/// Nhấn Q: Mở nắp xe cho Jason nhảy ra
	case DIK_Q:
	{
		SetIsFrozen(true);
		SwitchState(new StateOPENCabin(), NORMAL_STATE);
		CJason* jason = INSTANCE_JASON;
		_ACTIVE[JASON] = true;
		jason->nx = nx;
		jason->ResetAtPos(x + SOPHIA_BIG_BBOX_WIDTH / 2 - JASON_BIG_BBOX_WIDTH / 2, 
						  y - (SOPHIA_OPEN_CABIN_BBOX_HEIGHT - SOPHIA_SMALL_BBOX_HEIGHT));
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

/// <summary>
/// KIỂM TRA VA CHẠM VỚI BRICK
/// </summary>
void CSophia::CheckCollisionWithBrick(vector<LPGAMEOBJECT>* coObjects)
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

	//for (int i = 0; i < ListBrick.size(); i++)
	//{
	//	float brL, brT, brR, brB, plL, plT, plR, plB;
	//	ListBrick.at(i)->GetBoundingBox(brL, brT, brR, brB);
	//	GetBoundingBox(plL, plT, plR, plB);
	//	isColideUsingAABB =
	//		CGame::GetInstance()->IsCollidingAABB(plL, plT, plR, plB, brL, brT, brR, brB);
	//	
	//	if (isColideUsingAABB == true) 
	//	{
	//		if (plT < brT)	//TOP
	//		{
	//			if (plL < brL) //TOP LEFT
	//			{
	//				x = brL - SOPHIA_SMALL_BBOX_WIDTH - 0.4f;
	//			}
	//			else if (plR < brR) //TOP MID
	//			{
	//				y = brT - SOPHIA_SMALL_BBOX_HEIGHT - 0.4f;
	//			}
	//			else  //TOP RIGHT
	//			{
	//				x = brR + 0.4f;
	//			}

	//		}
	//		else if (brT < plT && plB > brB)  //BOT
	//		{
	//			if (plL < brL) //BOT LEFT
	//			{
	//				x = brL - SOPHIA_SMALL_BBOX_WIDTH - 0.4f;
	//			}
	//			else if (plR < brR) //BOT MID
	//			{
	//				y = brB + 0.4f;
	//			}
	//			else  //BOT RIGHT
	//			{
	//				x = brR + 0.4f;
	//			}
	//		}
	//		else if (plL < brL)  //LEFT
	//		{
	//			x = brL - SOPHIA_SMALL_BBOX_WIDTH - 0.4f;
	//		}
	//		else if (plR < brR) //MID
	//		{
	//			//do nothing
	//		}
	//		else  //RIGHR
	//		{
	//			x = brR + 0.4f;
	//		}


	//	}
	//
	//}
		
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

			LPCOLLISIONEVENT e = coEventsResult[0];
			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.4f;


			if (e->nx != 0) vx = 0;
			if (e->ny == -1)
			{
				vy = 0;
				lastColliBrick_y = e->obj->y;
			}
			else if (e->ny == 1)
			{
				vy = 0;
			}
		}
	}
	
}

/// <summary>
/// KIỂM TRA VA CHẠM VỚI PORTAL
/// </summary>
void CSophia::CheckCollisionWithPortal(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	vector<LPGAMEOBJECT> ListPortal;
	ListPortal.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (dynamic_cast<CPortal*>(coObjects->at(i)))
			ListPortal.push_back(coObjects->at(i));

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
			isAutoGo = true;
			autoGoDes = por->x_des - SOPHIA_BIG_BBOX_WIDTH;
			camera->miniScene_des = por->GetDesScene();
			D3DXVECTOR2 camPos = camera->GetCamPos();
			camera->SwitchScenePos = D3DXVECTOR2(camPos.x - camera->GetWidth(), camPos.y);
			((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->currentMiniScene = por->GetDesScene();
		}	
	}

}

/// <summary>
/// KIỂM TRA VA CHẠM VỚI VẬT PHẨM
/// </summary>
void CSophia::CheckCollisionWithItem(vector<LPGAMEOBJECT>* coObjects)
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
	if (isColideUsingAABB !=true)
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
	else if (type == 1)
	{
		this->numberFollowBullet += 1;
	}
	else if (type == 2)
	{
		this->numberThunderBullet += 1;
	}
	else if (type == 3)
	{
		this->numberThreeBullet += 1;
	}
}

/// <summary>
/// KIỂM TRA VA CHẠM VỚI QUÁI
/// </summary>
void CSophia::CheckCollisionWithEnemy(vector<LPGAMEOBJECT>* coObjects)
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
			isInjured = true;
			Sound::GetInstance()->Play("PlayerInjured", 0, 1);
		}
		

	}
	
}

void CSophia::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	/*if (currentAni->GetCurrentFrame() > -1)
	{
		RECT r = currentAni->GetFrameRect(currentAni->GetCurrentFrame());
		if (isGunUp)
		{
			if (nx > 0)
				left = x - 4;
			else
				left = x + 3;
		}
		else
			left = x;
		top = y + SOPHIA_SMALL_BBOX_HEIGHT - (r.bottom - r.top);
		right = left + (r.right - r.left);
		bottom = top + (r.bottom - r.top);
	}
	else
	{
		RECT r = currentAni->GetFrameRect(0);
		if (isGunUp)
		{
			if (nx > 0)
				left = x - 4;
			else
				left = x + 3;
		}
		else
			left = x;
		top = y + SOPHIA_SMALL_BBOX_HEIGHT - (r.bottom - r.top);
		right = left + (r.right - r.left);
		bottom = top + (r.bottom - r.top);
	}*/
	left = x;
	top = y;
	right = left + SOPHIA_SMALL_BBOX_WIDTH;
	bottom = top + SOPHIA_SMALL_BBOX_HEIGHT;
}


/// <summary>
/// HÀM TRẢ CHECK & CHO PHÉP NHÂN VẬT BẮN ĐẠN
/// </summary>
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

/// <summary>
/// HÀM RENDER OPEN CABIN STATE
/// </summary>
void CSophia::RenderOPENCabinAni()
{
	switch (frameID)
	{
	case -1:
	{
		lastFrameTime = GetTickCount64();
		frameID = 0;
		RECT r = currentAni->GetFrameRect(frameID);
		y_render = y + SOPHIA_SMALL_BBOX_HEIGHT - (r.bottom - r.top);

		currentAni->RenderFrame(frameID, x, y_render);
		break;
	}
	case 0:
	{
		DWORD t = currentAni->GetFrameTime(frameID);
		if (GetTickCount64() - lastFrameTime > t)
		{
			frameID = 1;
			lastFrameTime = GetTickCount64();
		}
		RECT r = currentAni->GetFrameRect(frameID);
		y_render = y + SOPHIA_SMALL_BBOX_HEIGHT - (r.bottom - r.top);

		currentAni->RenderFrame(frameID, x, y_render);
		break;
	}
	case 1:
	{
		DWORD t = currentAni->GetFrameTime(frameID);
		if (GetTickCount64() - lastFrameTime > t)
		{
			frameID = 1;
			lastFrameTime = GetTickCount64();
			isOpenCabin = false;
		}
		RECT r = currentAni->GetFrameRect(frameID);
		y_render = y + SOPHIA_SMALL_BBOX_HEIGHT - (r.bottom - r.top);

		currentAni->RenderFrame(frameID, x, y_render);
		break;
	}
	}
}

/// <summary>
/// HÀM TRẢ VỀ MÃ MÀU CẦN RENDER
/// </summary>
D3DCOLOR CSophia::GetRENDERColor()
{
	D3DCOLOR color;
	int alpha = 255;
	D3DCOLOR Orange = D3DCOLOR_ARGB(alpha, 250, 120, 90);
	D3DCOLOR Green = D3DCOLOR_ARGB(alpha, 0, 255, 153);
	D3DCOLOR Grey = D3DCOLOR_ARGB(alpha, 102, 153, 153);
	switch (colorID)
	{
	case 0:
	{
		color = Grey;
		colorID = 1;
		break;
	}
	case 1:
	{
		color = Grey;
		colorID = 2;
		break;
	}
	case 2:
	{
		color = Green;
		colorID = 3;
		break;
	}
	case 3:
	{
		color = Green;
		colorID = 4;
		break;
	}
	case 4:
	{
		color = Orange;
		colorID = 5;
		break;
	}
	case 5:
	{
		color = Orange;
		colorID = 0;
		break;
	}
	}
	return color;
}

/// <summary>
/// HÀM CHUYỂN ĐỔI TRẠNG THÁI NHÂN VẬT
/// </summary>
void CSophia::SwitchState(CState* state, int changeType)
{
	/*
		Tại hàm này, ta sẽ thay đổi state và animation hiện tại của player sang state, ani mới
	*/
	delete currentState;
	changeStateType = changeType;
	
	/* NẾU STATE CHUYỂN TỪ WALK -> IDLE: Set lại frameID để render đúng bánh xe */
	if (changeStateType == WALK2IDLE)
	{
		frameID = currentAni->GetCurrentFrame();
	}

	currentState = state;
	currentAni = animation_set->at(state->StateName);
}

/*
	Reset Sophia status to the beginning state of a scene
*/
void CSophia::Reset()
{
	SetPosition(start_x, start_y);
	SwitchState(new StateIDLE(), NORMAL_STATE);
	health = 8;

	SetSpeed(0, 0);
}

void CSophia::ResetAtPos(float _x, float _y)
{
	SetPosition(_x, _y);
	SwitchState(new StateIDLE(), NORMAL_STATE);
	SetSpeed(0, 0);
}

/// <summary>
/// HÀM AUTO DI CHUYỂN
/// </summary>
void CSophia::AutoGo(float x_des)
{
	if (nx > 0)
	{
		SwitchState(new StateWALKING(), NORMAL_STATE);
		if (x >= x_des)
			isAutoGo = false;
	}
	else
	{
		SwitchState(new StateWALKING(), NORMAL_STATE);
		if (x <= x_des)
			isAutoGo = false;
	}
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

CSophia* INSTANCE_SOPHIA
{
	if (__instance == NULL) {
		__instance = new CSophia();
	}
	return __instance;
}

