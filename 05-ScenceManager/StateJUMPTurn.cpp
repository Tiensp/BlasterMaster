#include "StateJUMPTurn.h"
#include "StateJUMP.h"
#include "StateTURN.h"
#include "StateWALKING.h"
#include "StateRAISEDGUN.h"
#include "StateIDLE.h"
#include "StateFALL.h"

StateJUMPTurn::StateJUMPTurn()
{
	CSophia* sophia = CSophia::GetInstance();
	sophia->SetIsTurning(true);
	if (sophia->nx < 0)
	{
		sophia->nx = 1;
		StateName = SOPHIA_JUMP_TURN_RIGHT;
	}
	else
	{
		sophia->nx = -1;
		StateName = SOPHIA_JUMP_TURN_LEFT;
	}
}

void StateJUMPTurn::Update()
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

void StateJUMPTurn::HandleKeyboard()
{
	CSophia* sophia = CSophia::GetInstance();

	if (!sophia->GetIsTurning())
	{
		if (!_KEYCODE[DIK_RIGHT] && !_KEYCODE[DIK_LEFT])
		{
			if (_ACTIVE[SOPHIA])
				sophia->SwitchState(new StateJUMP());
		}
		else if (_KEYCODE[DIK_RIGHT])
		{
			if (_ACTIVE[SOPHIA])
			{
				if (sophia->nx < 0)
				{
					sophia->SwitchState(new StateJUMPTurn());
					sophia->currentAni->ResetCurrentFrame();
				}
				else
				{
					sophia->SwitchState(new StateJUMP());
				}
			}

		}
		else if (_KEYCODE[DIK_LEFT])
		{
			if (_ACTIVE[SOPHIA])
			{
				if (sophia->nx > 0)
				{
					sophia->SwitchState(new StateJUMPTurn());
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

StateJUMPTurn::~StateJUMPTurn()
{
}
