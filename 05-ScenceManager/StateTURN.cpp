#include "StateTURN.h"
#include "StateIDLE.h"
#include "StateWALKING.h"

StateTURN::StateTURN()
{
	CSophia* sophia = CSophia::GetInstance();
	sophia->SetIsTurning(true);
	sophia->vx = 0;

	if (sophia->nx < 0)
	{
		sophia->nx = 1;
		StateName = SOPHIA_TURN_RIGHT;
	}
	else
	{
		sophia->nx = -1;
		StateName = SOPHIA_TURN_LEFT;
	}
}

void StateTURN::Update()
{
	this->HandleKeyboard();
}

void StateTURN::HandleKeyboard()
{
	CSophia* sophia = CSophia::GetInstance();
	if (!sophia->GetIsTurning())
	{
		if (!_KEYCODE[DIK_RIGHT] && !_KEYCODE[DIK_LEFT])
		{
			if (_ACTIVE[SOPHIA] && !sophia->GetIsFrozen())
				sophia->SwitchState(new StateIDLE());
		}
		else if (_KEYCODE[DIK_RIGHT])
		{
			if (_ACTIVE[SOPHIA] && !sophia->GetIsFrozen())
			{
				if (sophia->nx < 0)
				{
					sophia->SwitchState(new StateTURN());
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
			if (_ACTIVE[SOPHIA] && !sophia->GetIsFrozen())
			{
				if (sophia->nx > 0)
				{
					sophia->SwitchState(new StateTURN());
					sophia->currentAni->ResetCurrentFrame();
				}
				else
				{
					sophia->SwitchState(new StateWALKING());
				}
			}
		}
		
	}
}

StateTURN::~StateTURN()
{
}

