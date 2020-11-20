#include "StateJUMP.h"
#include "StateTURN.h"
#include "StateWALKING.h"
#include "StateRAISEDGUN.h"
#include "StateIDLE.h"

StateJUMP::StateJUMP()
{
	CSophia* sophia = CSophia::GetInstance();
	//sophia->vy = -0.03f*sophia->dt;
	sophia->vy = -SOPHIA_ACC_JUMP * sophia->dt;
	if (sophia->nx > 0)
	{
		StateName = SOPHIA_JUMP_RIGHT;
	}
	else
	{
		StateName = SOPHIA_JUMP_LEFT;
	}
}

void StateJUMP::Update()
{
	CSophia* sophia = CSophia::GetInstance();
	this->HandleKeyboard();
	if (sophia->vy > 0)
	{
		sophia->SwitchState(new StateIDLE());
	}
}

void StateJUMP::HandleKeyboard()
{
	CSophia* sophia = CSophia::GetInstance();

	/*if (_KEYCODE[DIK_RIGHT])
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
		sophia->SwitchState(new StateJUMP());*/
}

StateJUMP::~StateJUMP()
{
}
