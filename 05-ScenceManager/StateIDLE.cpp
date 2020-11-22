#include "StateIDLE.h"
#include "StateTURN.h"
#include "StateWALKING.h"
#include "StateRAISEDGUN.h"
#include "StateJUMP.h"

StateIDLE::StateIDLE()
{
	CSophia* sophia = CSophia::GetInstance();

	sophia->vx = 0;
	
	if (sophia->nx > 0)
	{
		StateName = SOPHIA_IDLE_RIGHT;
	}
	else
	{
		StateName = SOPHIA_IDLE_LEFT; 
	}
}

void StateIDLE::Update()
{
	this->HandleKeyboard();
}

void StateIDLE::HandleKeyboard()
{
	CSophia* sophia = CSophia::GetInstance();
	
	if (_KEYCODE[DIK_RIGHT])
	{
		if (_ACTIVE[SOPHIA])
		{
			if (sophia->nx < 0)
			{
				sophia->SwitchState(new StateTURN());
				sophia->currentAni->ResetCurrentFrame();
			}
			else
			{
				sophia->SwitchState(new StateWALKING());
				sophia->currentAni->ResetCurrentFrame();
			}
		}
	}
	else if (_KEYCODE[DIK_LEFT])
	{
		if (_ACTIVE[SOPHIA])
		{
			if (sophia->nx > 0)
			{
				sophia->SwitchState(new StateTURN());
				sophia->currentAni->ResetCurrentFrame();
			}
			else
			{
				sophia->SwitchState(new StateWALKING());
				sophia->currentAni->ResetCurrentFrame();
			}
		}
	}
	else if (_KEYCODE[DIK_UP])
	{
		if (_ACTIVE[SOPHIA])
		{
			sophia->SwitchState(new StateRAISEDGun());
			sophia->currentAni->ResetCurrentFrame();
		}
	}
	else if (_KEYCODE[DIK_DOWN])
	{
	}
	else
		sophia->SwitchState(new StateIDLE());
}

StateIDLE::~StateIDLE()
{
}
