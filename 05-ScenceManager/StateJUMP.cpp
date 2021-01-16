#include "StateJUMP.h"
#include "StateTURN.h"
#include "StateWALKING.h"
#include "StateRAISEDGUN.h"
#include "StateIDLEGunUP.h"
#include "StateIDLE.h"
#include "StateFALL.h"
#include "StateJUMPTurn.h"
#include "StateJUMPGunUP.h"
#include "StateFALLGunUP.h"

StateJUMP::StateJUMP()
{
	
	CSophia* sophia = INSTANCE_SOPHIA;
	sophia->renderFrame = false;

	if (_ACTIVE[SOPHIA] && !sophia->GetIsFrozen())
	{
		sophia->SetIsFalling(false);

		//Nếu chưa nhảy thì cho nhảy: set vy
		if (!sophia->GetIsJumping())
		{
			sophia->SetIsJumping(true);
			sophia->vy = -SOPHIA_JUMP_SPEED;
		}
		
		if (sophia->nx > 0)
		{
			StateName = SOPHIA_JUMP_RIGHT;
		}
		else
		{
			StateName = SOPHIA_JUMP_LEFT;
		}
		
	}
}

void StateJUMP::Update()
{
	CSophia* sophia = INSTANCE_SOPHIA;
	if (sophia->vy >= 0)
	{
			sophia->SwitchState(new StateFALL(), NORMAL_STATE);
	}
	else
		this->HandleKeyboard();
}

void StateJUMP::HandleKeyboard()
{
	CSophia* sophia = INSTANCE_SOPHIA;


	if (_KEYCODE[DIK_RIGHT])
	{
		if (_ACTIVE[SOPHIA] && !sophia->GetIsFrozen())
		{
			if (sophia->nx < 0)
			{
				sophia->SwitchState(new StateJUMPTurn(), NORMAL_STATE);
				sophia->currentAni->ResetCurrentFrame();
				sophia->vx = SOPHIA_WALKING_SPEED;
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
				sophia->SwitchState(new StateJUMPTurn(), NORMAL_STATE);
				sophia->currentAni->ResetCurrentFrame();
				sophia->vx = -SOPHIA_WALKING_SPEED;
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
			if (!sophia->GetIsGunUp())
			{
				sophia->SwitchState(new StateRAISEDGun(), NORMAL_STATE);
				sophia->currentAni->ResetCurrentFrame();
			}
			else
			{
				sophia->SwitchState(new StateJUMPGunUP(), NORMAL_STATE);
				sophia->currentAni->ResetCurrentFrame();
			}
			
		}
	}
	else if (_KEYCODE[DIK_DOWN])
	{
	}
	else
	{
		if (_ACTIVE[SOPHIA] && !sophia->GetIsFrozen())
		{	
			sophia->vx = 0;
		}
		else if (_ACTIVE[JASON])
		{
			INSTANCE_JASON->vx = 0;
		}
	}

	///////////////////
	// ACTIVE SOPHIA
	if (_ACTIVE[SOPHIA] && !sophia->GetIsFrozen())
	{
		if (!_KEYCODE[DIK_UP])
		{
			if (_KEYCODE[DIK_RIGHT])
			{
				if (sophia->nx < 0)
				{
					sophia->SwitchState(new StateJUMPTurn(), NORMAL_STATE);
					sophia->currentAni->ResetCurrentFrame();
					sophia->vx = SOPHIA_WALKING_SPEED;
				}
				else
				{
					sophia->vx = SOPHIA_WALKING_SPEED;
				}
			}
			else if (_KEYCODE[DIK_LEFT])
			{
				if (sophia->nx > 0)
				{
					sophia->SwitchState(new StateJUMPTurn(), NORMAL_STATE);
					sophia->currentAni->ResetCurrentFrame();
					sophia->vx = -SOPHIA_WALKING_SPEED;
				}
				else
				{
					sophia->vx = -SOPHIA_WALKING_SPEED;
				}
			}
		}
		else if (_KEYCODE[DIK_UP])
		{
			sophia->SwitchState(new StateRAISEDGun(), NORMAL_STATE);
			sophia->currentAni->ResetCurrentFrame();
		}
	}
	// ACTIVE JASON
	else if (_ACTIVE[JASON])
	{
		if (_KEYCODE[DIK_RIGHT])
		{
			CJason* jason = INSTANCE_JASON;
			jason->nx = 1;
			jason->SwitchState(new StateWALKING());
		}
		else if (_KEYCODE[DIK_LEFT])
		{
			CJason* jason = INSTANCE_JASON;
			jason->nx = -1;
			jason->SwitchState(new StateWALKING());
		}
	}
	else
	{
		if (_ACTIVE[SOPHIA] && !sophia->GetIsFrozen())
		{
			sophia->vx = 0;
		}
		else if (_ACTIVE[JASON])
		{
			INSTANCE_JASON->vx = 0;
		}
	}
}

StateJUMP::~StateJUMP()
{
}
