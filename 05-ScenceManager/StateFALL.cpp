#include "StateFALL.h"
#include "StateFALLTurn.h"
#include "StateTURN.h"
#include "StateWALKING.h"
#include "StateRAISEDGUN.h"
#include "StateIDLE.h"

StateFALL::StateFALL()
{
	
	CSophia* sophia = INSTANCE_SOPHIA;
	sophia->renderFrame = false;
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
	CSophia* sophia = INSTANCE_SOPHIA;
	if (sophia->vy == 0)
	{
		sophia->SetIsFalling(false);
		sophia->SwitchState(new StateIDLE(), WALK2IDLE);
	}
	else
		this->HandleKeyboard();
}

void StateFALL::HandleKeyboard()
{
	CSophia* sophia = INSTANCE_SOPHIA;

	if (_KEYCODE[DIK_RIGHT])
	{
		if (_ACTIVE[SOPHIA] && !sophia->GetIsFrozen())
		{
			if (sophia->nx < 0)
			{
				sophia->SwitchState(new StateFALLTurn(), NORMAL_STATE);
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
				sophia->SwitchState(new StateFALLTurn(), NORMAL_STATE);
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
			sophia->SwitchState(new StateRAISEDGun(), NORMAL_STATE);
			sophia->currentAni->ResetCurrentFrame();
		}
	}
	else if (_KEYCODE[DIK_DOWN])
	{
	}
	else
	{
		if (_ACTIVE[SOPHIA] && !sophia->GetIsFrozen())
			sophia->SwitchState(new StateFALL(), NORMAL_STATE);
	}
		
}

StateFALL::~StateFALL()
{
}
