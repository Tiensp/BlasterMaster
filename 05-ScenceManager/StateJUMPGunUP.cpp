#include "StateJUMPGunUP.h"
#include "StateJUMP.h"
#include "StateIDLE.h"
#include "StateFALL.h"
#include "StateFALLGunUP.h"

StateJUMPGunUP::StateJUMPGunUP()
{
	
	CSophia* sophia = INSTANCE_SOPHIA;
	sophia->renderFrame = false;
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

	RECT r = sophia->animation_set->at(StateName)->GetFrameRect(0);
	sophia->y_render = sophia->y + SOPHIA_SMALL_BBOX_HEIGHT - (r.bottom - r.top);
}

void StateJUMPGunUP::Update()
{
	CSophia* sophia = INSTANCE_SOPHIA;

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
		if (!sophia->GetIsGunUp())
			sophia->SwitchState(new StateFALL(), NORMAL_STATE);
		else
			sophia->SwitchState(new StateFALLGunUP(), NORMAL_STATE);
	}
	else
		this->HandleKeyboard();
}

void StateJUMPGunUP::HandleKeyboard()
{
	CSophia* sophia = INSTANCE_SOPHIA;

	if (_KEYCODE[DIK_UP])
	{
		if (_KEYCODE[DIK_RIGHT])
		{
			sophia->nx = 1;
			sophia->SwitchState(new StateJUMPGunUP(), NORMAL_STATE);
			sophia->vx = SOPHIA_WALKING_SPEED;
		}
		else if (_KEYCODE[DIK_LEFT])
		{
			sophia->nx = -1;
			sophia->SwitchState(new StateJUMPGunUP(), NORMAL_STATE);
			sophia->vx = -SOPHIA_WALKING_SPEED;
		}
	}
	else
	{
		/// Chưa có code hạ súng
		if (_ACTIVE[SOPHIA] && !sophia->GetIsFrozen())
		{
			sophia->vx = 0;
		}
		else if (_ACTIVE[JASON])
		{
			INSTANCE_JASON->vx = 0;
		}
	}
}

StateJUMPGunUP::~StateJUMPGunUP()
{
}
