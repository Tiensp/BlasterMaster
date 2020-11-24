#include "StateWALKING.h"
#include "StateIDLE.h"
#include "StateTURN.h"

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

	}
	else if (_ACTIVE[BIG_JASON])
	{
		CBigJason* bigJason = CBigJason::GetInstance();
		if (bigJason->nx > 0)
		{
			bigJason->vx = BIG_JASON_WALKING_SPEED;
			StateName = BIG_JASON_WALKING_RIGHT;
		}
		else if (bigJason->nx < 0)
		{
			bigJason->vx = -BIG_JASON_WALKING_SPEED;
			StateName = BIG_JASON_WALKING_LEFT;
		}
		else if (bigJason->ny > 0)
		{
			bigJason->vx = -BIG_JASON_WALKING_SPEED;
			StateName = BIG_JASON_WALKING_TOP;
		}
		else if (bigJason->ny < 0)
		{
			bigJason->vx = BIG_JASON_WALKING_SPEED;
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
				}
			}
			else if (_ACTIVE[JASON])
			{

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
				}
			}
			else if (_ACTIVE[JASON])
			{

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
				if (sophia->nx == -1)
				{

				}
				else
				{
					sophia->SwitchState(new StateWALKING());
				}
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
				CSophia* sophia = CSophia::GetInstance();
				sophia->SwitchState(new StateIDLE());
			}
			else if (_ACTIVE[BIG_JASON])
			{
				CBigJason* bigJason = CBigJason::GetInstance();
				bigJason->SwitchState(new StateIDLE());
			}
		}
	}
	else if (_ACTIVE[BIG_JASON])
	{
		CBigJason* bigJason = CBigJason::GetInstance();
		if (_KEYCODE[DIK_RIGHT] && _KEYCODE[DIK_UP])
		{
			bigJason->SwitchState(new StateWALKING());
			bigJason->nx = 1;
			bigJason->ny = 0;

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
