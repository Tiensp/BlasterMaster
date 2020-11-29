#include "StateIDLE.h"
#include "StateTURN.h"
#include "StateWALKING.h"
#include "StateRAISEDGUN.h"
#include "StateJUMP.h"

StateIDLE::StateIDLE()
{
	if (_ACTIVE[SOPHIA])
	{
		CSophia* sophia = CSophia::GetInstance();
		sophia->SetIsJumping(false);
		sophia->SetIsFalling(false);
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
	else if (_ACTIVE[JASON])
	{
		CJason* jason = CJason::GetInstance();

		jason->vx = 0;

		if (jason->nx > 0)
		{
			StateName = JASON_IDLE_RIGHT;
		}
		else
		{
			StateName = JASON_IDLE_LEFT;
		}
	}
	else if (_ACTIVE[BIG_JASON])
	{
		CBigJason* bigJason = CBigJason::GetInstance();

		bigJason->vx = 0;
		bigJason->vy = 0;

		if (bigJason->nx > 0)
		{
			StateName = BIG_JASON_IDLE_RIGHT;
		}
		else if (bigJason->nx < 0)
		{
			StateName = BIG_JASON_IDLE_LEFT;
		}
		else if (bigJason->ny > 0)
		{
			StateName = BIG_JASON_IDLE_TOP;
		}
		else if (bigJason->ny < 0)
		{
			StateName = BIG_JASON_IDLE_BOT;
		}
	}
}

void StateIDLE::Update()
{
	this->HandleKeyboard();
}

void StateIDLE::HandleKeyboard()
{
	if (_KEYCODE[DIK_RIGHT])
	{
		if (_ACTIVE[SOPHIA])
		{
			CSophia* sophia = CSophia::GetInstance();
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
		else if (_ACTIVE[JASON])
		{
			CJason* jason = CJason::GetInstance();
			jason->nx = 1;
			jason->SwitchState(new StateWALKING());
		}
		else if (_ACTIVE[BIG_JASON])
		{
			CBigJason* bigJason = CBigJason::GetInstance();
			bigJason->nx = 1;
			bigJason->ny = 0;
			bigJason->SwitchState(new StateWALKING());
		}
	}
	else if (_KEYCODE[DIK_LEFT])
	{
		if (_ACTIVE[SOPHIA])
		{
			CSophia* sophia = CSophia::GetInstance();
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
		else if (_ACTIVE[JASON])
		{
			CJason* jason = CJason::GetInstance();
			jason->nx = -1;
			jason->SwitchState(new StateWALKING());
		}
		else if (_ACTIVE[BIG_JASON])
		{
			CBigJason* bigJason = CBigJason::GetInstance();
			bigJason->nx = -1;
			bigJason->ny = 0;
			bigJason->SwitchState(new StateWALKING());
		}
	}
	else if (_KEYCODE[DIK_UP])
	{
		if (_ACTIVE[SOPHIA])
		{
			CSophia* sophia = CSophia::GetInstance();
			sophia->frameID = 0;
			sophia->SwitchState(new StateRAISEDGun());
			sophia->currentAni->ResetCurrentFrame();
		}
		else if (_ACTIVE[BIG_JASON])
		{
			CBigJason* bigJason = CBigJason::GetInstance();
			bigJason->nx = 0;
			bigJason->ny = 1;
			bigJason->SwitchState(new StateWALKING());
		}
	}
	else if (_KEYCODE[DIK_DOWN])
	{
		if (_ACTIVE[BIG_JASON])
		{
			CBigJason* bigJason = CBigJason::GetInstance();
			bigJason->nx = 0;
			bigJason->ny = -1;
			bigJason->SwitchState(new StateWALKING());
		}
	}
	else
	{
		if (_ACTIVE[SOPHIA]) 
		{
			CSophia* sophia = CSophia::GetInstance();
			sophia->SwitchState(new StateIDLE());
		}
		else if (_ACTIVE[JASON])
		{
			CJason* jason = CJason::GetInstance();
			jason->SwitchState(new StateIDLE());
		}
		else if (_ACTIVE[BIG_JASON])
		{
			CBigJason* bigJason = CBigJason::GetInstance();
			bigJason->SwitchState(new StateIDLE());
		}
	}
		
}

StateIDLE::~StateIDLE()
{
}
