#include "StateTURN.h"
#include "StateIDLE.h"
#include "StateWALKING.h"

StateTURN::StateTURN()
{
	CSophia* sophia = INSTANCE_SOPHIA;
	sophia->SetIsTurning(true);
	sophia->renderFrame = false;
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
	CSophia* sophia = INSTANCE_SOPHIA;
	if (!sophia->GetIsTurning())
	{
		if (!_KEYCODE[DIK_RIGHT] && !_KEYCODE[DIK_LEFT])
		{
			if (_ACTIVE[SOPHIA] && !sophia->GetIsFrozen())
				sophia->SwitchState(new StateIDLE(), WALK2IDLE);
		}
		else if (_KEYCODE[DIK_RIGHT])
		{
			if (_ACTIVE[SOPHIA] && !sophia->GetIsFrozen())
			{
				if (sophia->nx < 0)
				{
					sophia->SwitchState(new StateTURN(), NORMAL_STATE);
					sophia->currentAni->ResetCurrentFrame();
				}
				else
				{
					sophia->SwitchState(new StateWALKING(), IDLE2WALK);
				}
			}

		}
		else if (_KEYCODE[DIK_LEFT])
		{
			if (_ACTIVE[SOPHIA] && !sophia->GetIsFrozen())
			{
				if (sophia->nx > 0)
				{
					sophia->SwitchState(new StateTURN(), NORMAL_STATE);
					sophia->currentAni->ResetCurrentFrame();
				}
				else
				{
					sophia->SwitchState(new StateWALKING(), IDLE2WALK);
				}
			}
		}
		
	}
}

StateTURN::~StateTURN()
{
}

