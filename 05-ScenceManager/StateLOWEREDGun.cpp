#include "StateLOWEREDGun.h"
#include "StateIDLEGunUP.h"
#include "StateTURN.h"
#include "StateIDLE.h"
#include "StateWALKING.h"
#include "StateJUMP.h"
#include "StateFALL.h"

StateLOWEREDGun::StateLOWEREDGun()
{
	
	CSophia* sophia = INSTANCE_SOPHIA;
	sophia->renderFrame = false;
	sophia->SetIsLoweredGun(true);

	if (sophia->nx > 0)
	{
		StateName = SOPHIA_LOWERED_GUN_RIGHT;
	}
	else
	{
		StateName = SOPHIA_LOWERED_GUN_LEFT;
	}

	sophia->x_render = sophia->x;
	RECT r = sophia->animation_set->at(StateName)->GetFrameRect(0);
	sophia->y_render = sophia->y + SOPHIA_SMALL_BBOX_HEIGHT - (r.bottom - r.top);
}

void StateLOWEREDGun::Update()
{
	CSophia* sophia = INSTANCE_SOPHIA;
#pragma region Thay đổi x/y_render
	// Xem lại chú thích ở StateRAISEDGun
	int frameID = sophia->currentAni->GetCurrentFrame();
	if (sophia->currentAni->GetCurrentFrame() > -1)
	{
		RECT r = sophia->currentAni->GetFrameRect(frameID);
		sophia->y_render = sophia->y + SOPHIA_SMALL_BBOX_HEIGHT - (r.bottom - r.top) + 2;	
	}
	else
	{
		RECT r = sophia->currentAni->GetFrameRect(0);
		sophia->y_render = sophia->y + SOPHIA_SMALL_BBOX_HEIGHT - (r.bottom - r.top);
	}
#pragma endregion
	this->HandleKeyboard();
}

void StateLOWEREDGun::HandleKeyboard()
{
	CSophia* sophia = INSTANCE_SOPHIA;
	if (!sophia->GetIsLoweredGun())
	{
		if (sophia->GetIsJumping())
		{
			sophia->SwitchState(new StateJUMP(), NORMAL_STATE);
		}
		else if (sophia->GetIsFalling())
		{
			sophia->SwitchState(new StateFALL(), NORMAL_STATE);
		}
		else
		{
			sophia->SwitchState(new StateIDLE(), WALK2IDLE);
		}
	}
}

StateLOWEREDGun::~StateLOWEREDGun()
{
}


