#include "StateFALLTurn.h"
#include "StateFALL.h"
#include "StateIDLE.h"
#include "StateFALL.h"

StateFALLTurn::StateFALLTurn()
{
	
	CSophia* sophia = INSTANCE_SOPHIA;
	sophia->renderFrame = false;
	sophia->SetIsTurning(true);
	if (sophia->nx < 0)
	{
		sophia->nx = 1;
		StateName = SOPHIA_FALL_TURN_RIGHT;
	}
	else
	{
		sophia->nx = -1;
		StateName = SOPHIA_FALL_TURN_LEFT;
	}
}

void StateFALLTurn::Update()
{
	CSophia* sophia = INSTANCE_SOPHIA;
	if (sophia->vy == 0)
	{
		if (!sophia->GetIsTurning())
		{
			sophia->SetIsFalling(false);
			sophia->SwitchState(new StateIDLE(), WALK2IDLE);
		}	
	}
	else
		this->HandleKeyboard();
}

void StateFALLTurn::HandleKeyboard()
{
	CSophia* sophia = INSTANCE_SOPHIA;

	if (!sophia->GetIsTurning())
	{
		if (!_KEYCODE[DIK_RIGHT] && !_KEYCODE[DIK_LEFT])
		{
			sophia->SwitchState(new StateFALL(), NORMAL_STATE);
		}
		else if (_KEYCODE[DIK_RIGHT])
		{
			if (sophia->nx < 0)
			{
				sophia->SwitchState(new StateFALLTurn(), NORMAL_STATE);
				sophia->currentAni->ResetCurrentFrame();
			}
			else
			{
				sophia->SwitchState(new StateFALL(), NORMAL_STATE);
			}
		}
		else if (_KEYCODE[DIK_LEFT])
		{

			if (sophia->nx > 0)
			{
				sophia->SwitchState(new StateFALLTurn(), NORMAL_STATE);
				sophia->currentAni->ResetCurrentFrame();
			}
			else
			{
				sophia->SwitchState(new StateFALL(), NORMAL_STATE);
			}
			
		}

	}
}

StateFALLTurn::~StateFALLTurn()
{
}
