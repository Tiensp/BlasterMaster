#include "StateCRAWL.h"
#include "StateIDLE.h"
#include "StateWALKING.h"
#include "StateJUMP.h"

StateCRAWL::StateCRAWL()
{
	if (_ACTIVE[JASON])
	{
		CJason* jason = CJason::GetInstance();
		jason->vx = 0;
		if (jason->nx > 0)
		{
			StateName = JASON_CRAWL_RIGHT;
		}
		else
		{
			StateName = JASON_CRAWL_LEFT;
		}
	}
}

void StateCRAWL::Update()
{
	this->HandleKeyboard();
}

void StateCRAWL::HandleKeyboard()
{
	CJason* jason = CJason::GetInstance();
	if (_KEYCODE[DIK_RIGHT])
	{
		jason->nx = 1;
		jason->SwitchState(new StateCRAWL());
		jason->vx = JASON_WALKING_SPEED;
		jason->renderFrame = false;
	}
	else if (_KEYCODE[DIK_LEFT])
	{
		jason->nx = -1;
		jason->SwitchState(new StateCRAWL());
		jason->vx = -JASON_WALKING_SPEED;
		jason->renderFrame = false;
	}
	else
	{
		jason->SwitchState(new StateCRAWL());
		jason->renderFrame = true;
		jason->frameID = 0;
	}

}

StateCRAWL::~StateCRAWL()
{
}
