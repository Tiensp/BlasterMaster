#include "StateJUMPTurn.h"
#include "StateJUMP.h"
#include "StateIDLE.h"
#include "StateFALL.h"

StateJUMPTurn::StateJUMPTurn()
{
	CSophia* sophia = INSTANCE_SOPHIA;
	sophia->renderFrame = false;
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
	CSophia* sophia = INSTANCE_SOPHIA;
	if (sophia->vy >= 0)
	{
		if (!sophia->GetIsTurning())
		{
			sophia->SetIsJumping(false);
			sophia->SwitchState(new StateFALL(), NORMAL_STATE);
		}
	}
	else
		this->HandleKeyboard();
}

void StateJUMPTurn::HandleKeyboard()
{
	CSophia* sophia = INSTANCE_SOPHIA;

	if (!sophia->GetIsTurning())
	{
		if (!_KEYCODE[DIK_RIGHT] && !_KEYCODE[DIK_LEFT])
		{
			sophia->SwitchState(new StateJUMP(), NORMAL_STATE);
		}
		else if (_KEYCODE[DIK_RIGHT])
		{
			if (sophia->nx < 0)
			{
				sophia->SwitchState(new StateJUMPTurn(), NORMAL_STATE);
				sophia->currentAni->ResetCurrentFrame();
			}
			else
			{
				sophia->SwitchState(new StateJUMP(), NORMAL_STATE);
			}
		}
		else if (_KEYCODE[DIK_LEFT])
		{
			if (sophia->nx > 0)
			{
				sophia->SwitchState(new StateJUMPTurn(), NORMAL_STATE);
				sophia->currentAni->ResetCurrentFrame();
			}
			else
			{
				sophia->SwitchState(new StateJUMP(), NORMAL_STATE);
			}
		}

	}
}

StateJUMPTurn::~StateJUMPTurn()
{
}
