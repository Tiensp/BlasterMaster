#include "StateJUMP.h"
#include "StateTURN.h"
#include "StateWALKING.h"
#include "StateRAISEDGUN.h"
#include "StateIDLE.h"
#include "StateFALL.h"
#include "StateJUMPTurn.h"

StateJUMP::StateJUMP()
{
	CSophia* sophia = CSophia::GetInstance();

	sophia->vy = -SOPHIA_JUMP_SPEED;
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
	if (sophia->vy >= 0)
	{
		sophia->SetIsJumping(false);
		sophia->SwitchState(new StateFALL());
	}
	else
		this->HandleKeyboard();
}

void StateJUMP::HandleKeyboard()
{
	CSophia* sophia = CSophia::GetInstance();

	if (_KEYCODE[DIK_RIGHT])
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
				sophia->vx = SOPHIA_WALKING_SPEED;
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
				sophia->SwitchState(new StateJUMPTurn());
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

}

StateJUMP::~StateJUMP()
{
}
