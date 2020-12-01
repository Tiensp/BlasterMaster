#include "StateWALKING.h"
#include "StateIDLE.h"
#include "StateTURN.h"
#include "StateIDLEGunUP.h"
#include "StateRAISEDGun.h"
#include "StateWALKINGGunUP.h"

StateWALKING::StateWALKING()
{
	if (_ACTIVE[SOPHIA])
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
	else if (_ACTIVE[JASON])
	{
		CJason* jason = CJason::GetInstance();
		if (jason->nx > 0)
		{
			jason->vx = JASON_WALKING_SPEED;
			StateName = JASON_WALKING_RIGHT;
		}
		else
		{
			jason->vx = -JASON_WALKING_SPEED;
			StateName = JASON_WALKING_LEFT;
		}
	}
	else if (_ACTIVE[BIG_JASON])
	{
		CBigJason* bigJason = CBigJason::GetInstance();
		if (bigJason->nx > 0)
		{
			bigJason->vx = BIG_JASON_WALKING_SPEED;
			bigJason->vy = 0;
			StateName = BIG_JASON_WALKING_RIGHT;
		}
		else if (bigJason->nx < 0)
		{
			bigJason->vx = -BIG_JASON_WALKING_SPEED;
			bigJason->vy = 0;
			StateName = BIG_JASON_WALKING_LEFT;
		}
		else if (bigJason->ny > 0)
		{
			bigJason->vy = -BIG_JASON_WALKING_SPEED;
			bigJason->vx = 0;
			StateName = BIG_JASON_WALKING_TOP;
		}
		else if (bigJason->ny < 0)
		{
			bigJason->vy = BIG_JASON_WALKING_SPEED;
			bigJason->vx = 0;
			StateName = BIG_JASON_WALKING_BOT;
		}
	}
}

void StateWALKING::Update()
{
	this->HandleKeyboard();
}

void StateWALKING::HandleKeyboard()
{
	if (_ACTIVE[SOPHIA] || _ACTIVE[JASON])
	{
		if (_KEYCODE[DIK_UP] && _KEYCODE[DIK_RIGHT])
		{
			if (_ACTIVE[SOPHIA])
			{
				CSophia* sophia = CSophia::GetInstance();
				if (sophia->GetIsGunUp())
				{
					sophia->SwitchState(new StateWALKINGGunUP());
				}
				else
				{
					sophia->frameID = 0;
					sophia->SwitchState(new StateRAISEDGun());
					sophia->currentAni->ResetCurrentFrame();
				}
			}
		}
		else if (_KEYCODE[DIK_UP] && _KEYCODE[DIK_LEFT])
		{
			if (_ACTIVE[SOPHIA])
			{
				CSophia* sophia = CSophia::GetInstance();
				if (sophia->GetIsGunUp())
				{
					sophia->SwitchState(new StateWALKINGGunUP());
				}
				else
				{
					sophia->frameID = 0;
					sophia->SwitchState(new StateRAISEDGun());
					sophia->currentAni->ResetCurrentFrame();
				}
			}
		}
		else if (_KEYCODE[DIK_RIGHT])
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
				}
			}
			else if (_ACTIVE[JASON])
			{
				CJason* jason = CJason::GetInstance();
				jason->nx = 1;
				jason->SwitchState(new StateWALKING());
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
				}
			}
			else if (_ACTIVE[JASON])
			{
				CJason* jason = CJason::GetInstance();
				jason->nx = -1;
				jason->SwitchState(new StateWALKING());
			}
		}
		else if (_KEYCODE[DIK_UP])
		{
			if (_ACTIVE[SOPHIA])
			{
				CSophia* sophia = CSophia::GetInstance();
				if (sophia->GetIsGunUp())
				{
					sophia->SwitchState(new StateIDLEGunUP());
				}
				else
				{
					sophia->frameID = 0;
					sophia->SwitchState(new StateRAISEDGun());
					sophia->currentAni->ResetCurrentFrame();
				}
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
		}
	}
	else if (_ACTIVE[BIG_JASON])
	{
		CBigJason* bigJason = CBigJason::GetInstance();
		if (_KEYCODE[DIK_RIGHT] && _KEYCODE[DIK_UP])
		{
			bigJason->SwitchState(new StateWALKING());
			bigJason->vx = BIG_JASON_WALKING_SPEED;
			bigJason->vy = -BIG_JASON_WALKING_SPEED;
		}
		else if (_KEYCODE[DIK_RIGHT] && _KEYCODE[DIK_DOWN])
		{
			bigJason->SwitchState(new StateWALKING());
			bigJason->vx = BIG_JASON_WALKING_SPEED;
			bigJason->vy = BIG_JASON_WALKING_SPEED;
		}
		else if (_KEYCODE[DIK_LEFT] && _KEYCODE[DIK_UP])
		{
			bigJason->SwitchState(new StateWALKING());
			bigJason->vx = -BIG_JASON_WALKING_SPEED;
			bigJason->vy = -BIG_JASON_WALKING_SPEED;
		}
		else if (_KEYCODE[DIK_LEFT] && _KEYCODE[DIK_DOWN])
		{
			bigJason->SwitchState(new StateWALKING());
			bigJason->vx = -BIG_JASON_WALKING_SPEED;
			bigJason->vy = BIG_JASON_WALKING_SPEED;
		}
		else if (_KEYCODE[DIK_RIGHT])
		{
			bigJason->nx = 1;
			bigJason->ny = 0;
			bigJason->SwitchState(new StateWALKING());
		}
		else if (_KEYCODE[DIK_LEFT])
		{
			bigJason->nx = -1;
			bigJason->ny = 0;
			bigJason->SwitchState(new StateWALKING());
		}
		else if (_KEYCODE[DIK_UP])
		{
			bigJason->nx = 0;
			bigJason->ny = 1;
			bigJason->SwitchState(new StateWALKING());
		}
		else if (_KEYCODE[DIK_DOWN])
		{
			bigJason->nx = 0;
			bigJason->ny = -1;
			bigJason->SwitchState(new StateWALKING());
		}
		else
		{
			bigJason->SwitchState(new StateIDLE());
		}
	}
}

StateWALKING::~StateWALKING()
{
}
