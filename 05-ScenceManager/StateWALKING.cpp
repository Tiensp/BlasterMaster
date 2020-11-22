#include "StateWALKING.h"
#include "StateIDLE.h"
#include "StateTURN.h"

StateWALKING::StateWALKING()
{
	CSophia* sophia = CSophia::GetInstance();
	if (sophia->nx > 0)
	{
		sophia->vx = SOPHIA_WALKING_SPEED;
		StateName = SOPHIA_WALKING_RIGHT;
	}
	else
	{
		sophia->vx = -SOPHIA_WALKING_SPEED;
		StateName = SOPHIA_WALKING_LEFT;
	}
}

void StateWALKING::Update()
{
	this->HandleKeyboard();
}

void StateWALKING::HandleKeyboard()
{
	CSophia* sophia = CSophia::GetInstance();
	if (!_KEYCODE[DIK_RIGHT] && !_KEYCODE[DIK_LEFT])
	{
		if (_ACTIVE[SOPHIA])
			sophia->SwitchState(new StateIDLE());
	}
	else if (_KEYCODE[DIK_RIGHT])
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
			}
		}
	}
	else if (_KEYCODE[DIK_UP])
	{
		if (_ACTIVE[SOPHIA])
		{
			if (sophia->nx == -1)
			{
				
			}
			else
			{
				sophia->SwitchState(new StateWALKING());
			}
		}
	}
	else if (_KEYCODE[DIK_DOWN])
	{
		if (_ACTIVE[SOPHIA])
		{
			if (sophia->nx == -1)
			{
				
			}
			else
			{
				sophia->SwitchState(new StateWALKING());
			}
		}
	}
}

StateWALKING::~StateWALKING()
{
}
