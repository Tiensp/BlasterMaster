#include "StateWALKINGGunUP.h"
#include "StateWALKING.h"
#include "StateIDLE.h"
#include "StateIDLEGunUP.h"
#include "StateTURN.h"
#include "StateLOWEREDGun.h"

StateWALKINGGunUP::StateWALKINGGunUP()
{
	CSophia* sophia = CSophia::GetInstance();
	sophia->SetIsGunUp(true);
	if (sophia->nx > 0)
	{
		sophia->x_render = sophia->x - 4;
		sophia->vx = SOPHIA_WALKING_SPEED;
		StateName = SOPHIA_WALKING_GUN_UP_RIGHT;
	}
	else
	{
		sophia->x_render = sophia->x + 3;
		sophia->vx = -SOPHIA_WALKING_SPEED;
		StateName = SOPHIA_WALKING_GUN_UP_LEFT;
	}
}

void StateWALKINGGunUP::Update()
{
	CSophia* sophia = CSophia::GetInstance();
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
	this->HandleKeyboard();
}

void StateWALKINGGunUP::HandleKeyboard()
{
	CSophia* sophia = CSophia::GetInstance();
	if (_KEYCODE[DIK_UP])
	{
		if (_KEYCODE[DIK_RIGHT])
		{
			sophia->nx = 1;
			sophia->SwitchState(new StateWALKINGGunUP());
		}
		else if (_KEYCODE[DIK_LEFT])
		{
			sophia->nx = -1;
			sophia->SwitchState(new StateWALKINGGunUP());
		}
		else
		{
			sophia->SwitchState(new StateIDLEGunUP());
		}
	}
	else
	{
		sophia->SetIsGunUp(false);
		sophia->frameID = 0;
		sophia->SwitchState(new StateLOWEREDGun());
		sophia->currentAni->ResetCurrentFrame();
	}
}

StateWALKINGGunUP::~StateWALKINGGunUP()
{
}
