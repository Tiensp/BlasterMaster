#include "StateCLIMB.h"


StateCLIMB::StateCLIMB()
{
	if (_ACTIVE[JASON])
	{
		CJason* jason = INSTANCE_JASON;
		jason->vx = 0;
		jason->vy = 0;
		jason->renderFrame = false;
		StateName = JASON_CLIMB;
	}
}

void StateCLIMB::Update()
{
	CJason* jason = INSTANCE_JASON;
	jason->vx = 0;
	jason->vy = 0;
	jason->renderFrame = true;
	jason->frameID = 0;
	this->HandleKeyboard();
}

void StateCLIMB::HandleKeyboard()
{
	CJason* jason = INSTANCE_JASON;
	if (_KEYCODE[DIK_UP])
	{
		
		jason->SwitchState(new StateCLIMB());
		jason->ny = -1;
		jason->vx = 0;
		jason->vy = -JASON_CLIMB_SPEED;
		jason->renderFrame = false;
	}
	if (_KEYCODE[DIK_DOWN])
	{
		
		jason->SwitchState(new StateCLIMB());
		jason->ny = 1;
		jason->vx = 0;
		jason->vy = JASON_CLIMB_SPEED;
		jason->renderFrame = false;
	}
	/*else if (_KEYCODE[DIK_LEFT])
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
	}*/
}

StateCLIMB::~StateCLIMB()
{
}
