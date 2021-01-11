#include "StateOPENCabin.h"
#include "Sophia.h"
#include "Jason.h"


StateOPENCabin::StateOPENCabin()
{
	CSophia* sophia = CSophia::GetInstance();
	sophia->SetIsFrozen(true);
	sophia->renderFrame = true;
	sophia->frameID = -1;

	if (sophia->nx > 0)
	{
		StateName = SOPHIA_OPEN_CABIN_RIGHT;
	}
	else
	{
		StateName = SOPHIA_OPEN_CABIN_LEFT;
	}
}

void StateOPENCabin::Update()
{
	//this->HandleKeyboard();
}

void StateOPENCabin::HandleKeyboard()
{
}

StateOPENCabin::~StateOPENCabin()
{
}
