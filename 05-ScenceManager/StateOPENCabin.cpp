#include "StateOPENCabin.h"
#include "StateIDLE.h"
#include "Sophia.h"
#include "Jason.h"


StateOPENCabin::StateOPENCabin()
{
	
	CSophia* sophia = INSTANCE_SOPHIA;
	sophia->frameID = -1;
	sophia->vx = 0;
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
	CSophia* sophia = INSTANCE_SOPHIA;
		if (!sophia->GetIsOpenCabin())
			sophia->SwitchState(new StateIDLE(), NORMAL_STATE);
}

void StateOPENCabin::HandleKeyboard()
{
}

StateOPENCabin::~StateOPENCabin()
{
}
