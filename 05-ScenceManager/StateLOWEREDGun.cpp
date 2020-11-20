#include "StateLOWEREDGun.h"
#include "StateIDLEGunUP.h"
#include "StateTURN.h"
#include "StateIDLE.h"
#include "StateWALKING.h"

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
}

void StateLOWEREDGun::Update()
{
	this->HandleKeyboard();
}

void StateLOWEREDGun::HandleKeyboard()
{
	CSophia* sophia = CSophia::GetInstance();
	if (!sophia->GetIsLoweredGun())
	{
			sophia->SwitchState(new StateIDLE());
		/*else if (_KEYCODE[DIK_RIGHT])
		{
			if (_ACTIVE[SOPHIA])
			{
				if (sophia->nx < 0)
				{
					sophia->SwitchState(new StateLOWEREDGun());
					sophia->currentAni->ResetCurrentFrame();
				}
				else
				{
					sophia->SwitchState(new StateWALKING());
				}
			}

		}
		else if (_KEYCODE[DIK_LEFT])
		{
			if (_ACTIVE[SOPHIA])
			{
				if (sophia->nx > 0)
				{
					sophia->SwitchState(new StateLOWEREDGun());
					sophia->currentAni->ResetCurrentFrame();
				}
				else
				{
					sophia->SwitchState(new StateWALKING());
				}
			}
		}*/

	}
}

StateLOWEREDGun::~StateLOWEREDGun()
{
}


