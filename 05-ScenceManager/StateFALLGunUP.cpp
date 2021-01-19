#include "StateFALLGunUP.h"
#include "StateFALL.h"
#include "StateFALLTurn.h"
#include "StateTURN.h"
#include "StateWALKING.h"
#include "StateRAISEDGUN.h"
#include "StateIDLE.h"
#include "StateJUMP.h"
#include "StateIDLEGunUP.h"

StateFALLGunUP::StateFALLGunUP()
{

	CSophia* sophia = INSTANCE_SOPHIA;
	sophia->renderFrame = false;
	sophia->SetIsFalling(true);
	sophia->SetIsJumping(false);

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

void StateFALLGunUP::Update()
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

	if (sophia->vy == 0)
	{
		if (!sophia->GetIsGunUp())
			sophia->SwitchState(new StateIDLE(), WALK2IDLE);
		else
			sophia->SwitchState(new StateIDLEGunUP(), WALK2IDLE);
	}
	else
		this->HandleKeyboard();
}

void StateFALLGunUP::HandleKeyboard()
{
	CSophia* sophia = INSTANCE_SOPHIA;

	if (_KEYCODE[DIK_UP])
	{
		if (_ACTIVE[SOPHIA] && !sophia->GetIsFrozen())
		{
			if (_KEYCODE[DIK_RIGHT])
			{
				if (sophia->nx < 0)
				{
					sophia->nx = 1;
					sophia->SwitchState(new StateFALLGunUP(), NORMAL_STATE);
					sophia->currentAni->ResetCurrentFrame();
				}
				else
				{
					sophia->vx = SOPHIA_WALKING_SPEED;
				}
				
			}
			else if (_KEYCODE[DIK_LEFT])
			{
				if (_ACTIVE[SOPHIA] && !sophia->GetIsFrozen())
				{
					if (sophia->nx > 0)
					{
						sophia->nx = -1;
						sophia->SwitchState(new StateFALLGunUP(), NORMAL_STATE);
						sophia->currentAni->ResetCurrentFrame();
					}
					else
					{
						sophia->vx = -SOPHIA_WALKING_SPEED;
					}
				}
			}
		}
	}
	else if (_KEYCODE[DIK_DOWN])
	{
	}
	else
	{
		if (_ACTIVE[SOPHIA] && !sophia->GetIsFrozen())
			sophia->SwitchState(new StateFALL(), NORMAL_STATE);
	}

}

StateFALLGunUP::~StateFALLGunUP()
{
}
