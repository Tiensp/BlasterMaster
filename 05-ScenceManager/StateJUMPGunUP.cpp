#include "StateJUMPGunUP.h"
#include "StateJUMP.h"
#include "StateIDLE.h"
#include "StateFALL.h"

StateJUMPGunUP::StateJUMPGunUP()
{
	CSophia* sophia = CSophia::GetInstance();
	sophia->SetIsGunUp(true);
	if (sophia->nx < 0)
	{
		StateName = SOPHIA_IDLE_GUN_UP_RIGHT;
	}
	else
	{
		StateName = SOPHIA_IDLE_GUN_UP_LEFT;
	}
}

void StateJUMPGunUP::Update()
{
	CSophia* sophia = CSophia::GetInstance();
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

	if (!sophia->GetIsTurning())
	{
		if (!_KEYCODE[DIK_RIGHT] && !_KEYCODE[DIK_LEFT])
		{
			sophia->SwitchState(new StateJUMP());
		}
		else if (_KEYCODE[DIK_RIGHT])
		{
			if (sophia->nx < 0)
			{
				sophia->SwitchState(new StateJUMPGunUP());
				sophia->currentAni->ResetCurrentFrame();
			}
			else
			{
				sophia->SwitchState(new StateJUMP());
			}
		}
		else if (_KEYCODE[DIK_LEFT])
		{
			if (_ACTIVE[SOPHIA])
			{
				if (sophia->nx > 0)
				{
					sophia->SwitchState(new StateJUMPGunUP());
					sophia->currentAni->ResetCurrentFrame();
				}
				else
				{
					sophia->SwitchState(new StateJUMP());
				}
			}
		}

	}
}

StateJUMPGunUP::~StateJUMPGunUP()
{
}
