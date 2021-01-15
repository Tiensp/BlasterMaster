#include "StateIDLE.h"
#include "StateTURN.h"
#include "StateWALKING.h"
#include "StateRAISEDGUN.h"
#include "StateJUMP.h"

StateIDLE::StateIDLE()
{
	
	CSophia* sophia = INSTANCE_SOPHIA;
	sophia->renderFrame = true;
	if (_ACTIVE[SOPHIA] && !sophia->GetIsFrozen())
	{
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
		CJason* jason = INSTANCE_JASON;

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
		CBigJason* bigJason = INSTANCE_BIGJASON;

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
	CSophia* sophia = INSTANCE_SOPHIA;

	if (_KEYCODE[DIK_RIGHT])
	{
		if (_ACTIVE[SOPHIA] && !sophia->GetIsFrozen())
		{
			if (sophia->nx < 0)
			{
				sophia->SwitchState(new StateTURN(), NORMAL_STATE);
				sophia->currentAni->ResetCurrentFrame();
			}
			else
			{
				sophia->SwitchState(new StateWALKING(), IDLE2WALK);
				sophia->currentAni->ResetCurrentFrame();
			}
		}
		else if (_ACTIVE[JASON])
		{
			CJason* jason = INSTANCE_JASON;
			jason->nx = 1;
			jason->SwitchState(new StateWALKING());
		}
		else if (_ACTIVE[BIG_JASON])
		{
			CBigJason* bigJason = INSTANCE_BIGJASON;
			bigJason->nx = 1;
			bigJason->ny = 0;
			bigJason->SwitchState(new StateWALKING());
		}
	}
	else if (_KEYCODE[DIK_LEFT])
	{
		if (_ACTIVE[SOPHIA] && !sophia->GetIsFrozen())
		{
			if (sophia->nx > 0)
			{
				sophia->SwitchState(new StateTURN(), NORMAL_STATE);
				sophia->currentAni->ResetCurrentFrame();
			}
			else
			{
				sophia->SwitchState(new StateWALKING(), IDLE2WALK);
				sophia->currentAni->ResetCurrentFrame();
			}
		}
		else if (_ACTIVE[JASON])
		{
			CJason* jason = INSTANCE_JASON;
			jason->nx = -1;
			jason->SwitchState(new StateWALKING());
		}
		else if (_ACTIVE[BIG_JASON])
		{
			CBigJason* bigJason = INSTANCE_BIGJASON;
			bigJason->nx = -1;
			bigJason->ny = 0;
			bigJason->SwitchState(new StateWALKING());
		}
	}
	else if (_KEYCODE[DIK_UP])
	{
		if (_ACTIVE[SOPHIA] && !sophia->GetIsFrozen())
		{
			sophia->SwitchState(new StateRAISEDGun(), NORMAL_STATE);
			sophia->currentAni->ResetCurrentFrame();
		}
		else if (_ACTIVE[BIG_JASON])
		{
			CBigJason* bigJason = INSTANCE_BIGJASON;
			bigJason->nx = 0;
			bigJason->ny = 1;
			bigJason->SwitchState(new StateWALKING());
		}
	}
	else if (_KEYCODE[DIK_DOWN])
	{
		if (_ACTIVE[BIG_JASON])
		{
			CBigJason* bigJason = INSTANCE_BIGJASON;
			bigJason->nx = 0;
			bigJason->ny = -1;
			bigJason->SwitchState(new StateWALKING());
		}
	}
	else
	{
		if (_ACTIVE[SOPHIA] && !sophia->GetIsFrozen()) 
		{
			sophia->SwitchState(new StateIDLE(), NORMAL_STATE);
		}
		else if (_ACTIVE[JASON])
		{
			CJason* jason = INSTANCE_JASON;
			jason->SwitchState(new StateIDLE());
		}
		else if (_ACTIVE[BIG_JASON])
		{
			CBigJason* bigJason = INSTANCE_BIGJASON;
			bigJason->SwitchState(new StateIDLE());
		}
	}
		
}

StateIDLE::~StateIDLE()
{
}
