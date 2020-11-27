#include "StateFALLTurn.h"
#include "StateFALL.h"
#include "StateIDLE.h"
#include "StateFALL.h"

StateFALLTurn::StateFALLTurn()
{
	CSophia* sophia = CSophia::GetInstance();
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
	CSophia* sophia = CSophia::GetInstance();
	if (sophia->vy == 0)
	{
		if (!sophia->GetIsTurning())
		{
			sophia->SetIsFalling(false);
			sophia->SwitchState(new StateIDLE());
		}	
	}
	else
		this->HandleKeyboard();
}

void StateFALLTurn::HandleKeyboard()
{
	CSophia* sophia = CSophia::GetInstance();

	if (!sophia->GetIsTurning())
	{
		if (!_KEYCODE[DIK_RIGHT] && !_KEYCODE[DIK_LEFT])
		{
			sophia->SwitchState(new StateFALL());
		}
		else if (_KEYCODE[DIK_RIGHT])
		{
			if (sophia->nx < 0)
			{
				sophia->SwitchState(new StateFALLTurn());
				sophia->currentAni->ResetCurrentFrame();
			}
			else
			{
				sophia->SwitchState(new StateFALL());
			}
		}
		else if (_KEYCODE[DIK_LEFT])
		{
			if (_ACTIVE[SOPHIA])
			{
				if (sophia->nx > 0)
				{
					sophia->SwitchState(new StateFALLTurn());
					sophia->currentAni->ResetCurrentFrame();
				}
				else
				{
					sophia->SwitchState(new StateFALL());
				}
			}
		}

	}
}

StateFALLTurn::~StateFALLTurn()
{
}
