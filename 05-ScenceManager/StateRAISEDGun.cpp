#include "StateRAISEDGun.h"
#include "StateTURN.h"
#include "StateIDLE.h"
#include "StateWALKING.h"
#include "StateIDLEGunUP.h"
#include "StateLOWEREDGun.h"

StateRAISEDGun::StateRAISEDGun()
{
	CSophia* sophia = CSophia::GetInstance();
	sophia->SetIsRaisedGun(true);

	if (sophia->nx > 0)
	{
		StateName = SOPHIA_RAISED_GUN_RIGHT;
	}
	else
	{
		StateName = SOPHIA_RAISED_GUN_LEFT;
	}
}

void StateRAISEDGun::Update()
{
	this->HandleKeyboard();
}

void StateRAISEDGun::HandleKeyboard()
{
	CSophia* sophia = CSophia::GetInstance();
	if (!sophia->GetIsRaisedGun())
	{
		if (_KEYCODE[DIK_UP])
		{
			sophia->SwitchState(new StateIDLEGunUP());
		}
		else
		{
			sophia->SwitchState(new StateIDLE());
		}
			
	}
}

StateRAISEDGun::~StateRAISEDGun()
{
}


