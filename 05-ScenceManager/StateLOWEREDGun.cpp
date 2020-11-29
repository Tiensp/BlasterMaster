#include "StateLOWEREDGun.h"
#include "StateIDLEGunUP.h"
#include "StateTURN.h"
#include "StateIDLE.h"
#include "StateWALKING.h"
#include "StateJUMP.h"
#include "StateFALL.h"

StateLOWEREDGun::StateLOWEREDGun()
{
	CSophia* sophia = CSophia::GetInstance();
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
	RECT r = sophia->animation_set->at(StateName)->GetFrameRect(sophia->frameID);
	sophia->y_render = sophia->y + SOPHIA_SMALL_BBOX_HEIGHT - (r.bottom - r.top);
}

void StateLOWEREDGun::Update()
{
	CSophia* sophia = CSophia::GetInstance();
#pragma region Thay đổi x/y_render
	// Xem lại chú thích ở StateRAISEDGun
	sophia->frameID = sophia->currentAni->GetCurrentFrame();
	if (sophia->currentAni->GetCurrentFrame() > -1)
	{
		if (sophia->currentAni->GetCurrentFrame() == 2)
		{
			RECT r = sophia->currentAni->GetFrameRect(sophia->frameID);
			sophia->y_render = sophia->y + SOPHIA_SMALL_BBOX_HEIGHT - (r.bottom - r.top) + 2;
		}
		else
		{
			RECT r = sophia->currentAni->GetFrameRect(sophia->frameID);
			sophia->y_render = sophia->y + SOPHIA_SMALL_BBOX_HEIGHT - (r.bottom - r.top) + 2;
		}
	}
	else
	{
		sophia->frameID = 0;
		RECT r = sophia->currentAni->GetFrameRect(sophia->frameID);
		sophia->y_render = sophia->y + SOPHIA_SMALL_BBOX_HEIGHT - (r.bottom - r.top);
	}
#pragma endregion
	this->HandleKeyboard();
}

void StateLOWEREDGun::HandleKeyboard()
{
	CSophia* sophia = CSophia::GetInstance();
	if (!sophia->GetIsLoweredGun())
	{
		if (sophia->GetIsJumping())
		{
			sophia->SwitchState(new StateJUMP());
		}
		else if (sophia->GetIsFalling())
		{
			sophia->SwitchState(new StateFALL());
		}
		else
		{
			sophia->SwitchState(new StateIDLE());
		}
	}
}

StateLOWEREDGun::~StateLOWEREDGun()
{
}


