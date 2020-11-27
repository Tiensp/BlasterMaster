#include "StateIDLEGunUP.h"
#include "StateTURN.h"
#include "StateIDLE.h"
#include "StateWALKING.h"
#include "StateLOWEREDGun.h"
#include "StateWALKINGGunUP.h"

StateIDLEGunUP::StateIDLEGunUP()
{
	CSophia* sophia = CSophia::GetInstance();
	sophia->SetIsGunUp(true);
	sophia->vx = 0;

	if (sophia->nx > 0)
	{
		StateName = SOPHIA_IDLE_GUN_UP_RIGHT;
	}
	else
	{
		StateName = SOPHIA_IDLE_GUN_UP_LEFT;
	}
}

void StateIDLEGunUP::Update()
{
	this->HandleKeyboard();
}

void StateIDLEGunUP::HandleKeyboard()
{
	CSophia* sophia = CSophia::GetInstance();
	if (!sophia->GetIsRaisedGun())
	{
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
			sophia->SwitchState(new StateLOWEREDGun());
			sophia->currentAni->ResetCurrentFrame();
		}
			
		
	}
}

StateIDLEGunUP::~StateIDLEGunUP()
{
}


