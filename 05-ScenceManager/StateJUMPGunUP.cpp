#include "StateJUMPGunUP.h"
#include "StateJUMP.h"
#include "StateIDLE.h"
#include "StateFALL.h"

StateJUMPGunUP::StateJUMPGunUP()
{
	CSophia* sophia = CSophia::GetInstance();
	sophia->SetIsGunUp(true);

	if (!sophia->GetIsJumping())	// Nếu chưa nhảy thì cho nhảy
	{
		sophia->SetIsJumping(true);
		sophia->vy = -SOPHIA_JUMP_SPEED;
	}

	if (sophia->nx > 0)
	{
		sophia->x_render = sophia->x - 4;
		StateName = SOPHIA_IDLE_GUN_UP_RIGHT;
	}
	else
	{
		sophia->x_render = sophia->x + 3;
		StateName = SOPHIA_IDLE_GUN_UP_LEFT;
	}
}

void StateJUMPGunUP::Update()
{
	CSophia* sophia = CSophia::GetInstance();

#pragma region Thay đổi x/y_render
	// Xem lại chú thích y_render ở StateRAISEDGun
	if (sophia->nx > 0)
		sophia->x_render = sophia->x - 4;
	else
		sophia->x_render = sophia->x + 3;

	if (sophia->currentAni->GetCurrentFrame() > -1)
	{
		RECT r = sophia->currentAni->GetFrameRect(sophia->currentAni->GetCurrentFrame());
		sophia->y_render = sophia->y + SOPHIA_SMALL_BBOX_HEIGHT - (r.bottom - r.top);
	}
	else
	{
		RECT r = sophia->currentAni->GetFrameRect(0);
		sophia->y_render = sophia->y + SOPHIA_SMALL_BBOX_HEIGHT - (r.bottom - r.top);
	}
#pragma endregion

	if (sophia->vy >= 0)
	{
		sophia->SetIsJumping(false);
		sophia->SwitchState(new StateFALL());
	}
	else
		this->HandleKeyboard();
}

void StateJUMPGunUP::HandleKeyboard()
{
	CSophia* sophia = CSophia::GetInstance();

	if (_KEYCODE[DIK_UP])
	{
		if (!_KEYCODE[DIK_RIGHT] && !_KEYCODE[DIK_LEFT])
		{
			sophia->SwitchState(new StateJUMPGunUP());
		}
		else if (_KEYCODE[DIK_RIGHT])
		{
			sophia->nx = 1;
			sophia->SwitchState(new StateJUMPGunUP());
			sophia->vx = SOPHIA_WALKING_SPEED;
		}
		else if (_KEYCODE[DIK_LEFT])
		{
			sophia->nx = -1;
			sophia->SwitchState(new StateJUMPGunUP());
			sophia->vx = SOPHIA_WALKING_SPEED;
		}
	}
	else
	{

	}
}

StateJUMPGunUP::~StateJUMPGunUP()
{
}
