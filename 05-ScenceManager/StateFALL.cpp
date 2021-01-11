#include "StateFALL.h"
#include "StateFALLTurn.h"
#include "StateTURN.h"
#include "StateWALKING.h"
#include "StateRAISEDGUN.h"
#include "StateIDLE.h"

StateFALL::StateFALL()
{
	CSophia* sophia = CSophia::GetInstance();
	sophia->SetIsFalling(true);


	if (sophia->nx > 0)
	{
		StateName = SOPHIA_FALL_RIGHT;
	}
	else
	{
		StateName = SOPHIA_FALL_LEFT;
	}
}

void StateFALL::Update()
{
	CSophia* sophia = CSophia::GetInstance();
	if (sophia->vy == 0)
	{
		sophia->SetIsFalling(false);
		sophia->SwitchState(new StateIDLE());
	}
	else
		this->HandleKeyboard();
}

void StateFALL::HandleKeyboard()
{
	CSophia* sophia = CSophia::GetInstance();

	if (_KEYCODE[DIK_RIGHT])
	{
		if (_ACTIVE[SOPHIA] && !sophia->GetIsFrozen())
		{
			if (sophia->nx < 0)
			{
				sophia->SwitchState(new StateFALLTurn());
				sophia->currentAni->ResetCurrentFrame();
			}
			else
			{
				sophia->vx = SOPHIA_WALKING_SPEED;
			}
		}
	}
	else if (_KEYCODE[DIK_LEFT])
	{
		if (_ACTIVE[SOPHIA] && !sophia->GetIsFrozen())
		{
			if (sophia->nx > 0)
			{
				sophia->SwitchState(new StateFALLTurn());
				sophia->currentAni->ResetCurrentFrame();
			}
			else
			{
				sophia->vx = -SOPHIA_WALKING_SPEED;
			}
		}
	}
	else if (_KEYCODE[DIK_UP])
	{
		if (_ACTIVE[SOPHIA] && !sophia->GetIsFrozen())
		{
			sophia->frameID = 0;
			sophia->SwitchState(new StateRAISEDGun());
			sophia->currentAni->ResetCurrentFrame();
		}
	}
	else if (_KEYCODE[DIK_DOWN])
	{
	}
	else
	{
		if (_ACTIVE[SOPHIA] && !sophia->GetIsFrozen())
			sophia->SwitchState(new StateFALL());
	}
		
}

StateFALL::~StateFALL()
{
}
