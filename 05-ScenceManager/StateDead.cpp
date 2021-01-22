#include "StateDead.h"

StateDead::StateDead()
{
	CSophia* sophia = INSTANCE_SOPHIA;
	sophia->renderFrame = false;
	if (_ACTIVE[SOPHIA] )
	{
	
		sophia->vx = 0;
		sophia->vy = 0;
		StateName = SOPHIA_DIE;
		sophia->SetIsDead(true);
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
	RECT r = sophia->animation_set->at(StateName)->GetFrameRect(0);
	sophia->y_render = sophia->y + SOPHIA_SMALL_BBOX_HEIGHT - (r.bottom - r.top);
}

void StateDead::Update()
{
	if (_ACTIVE[SOPHIA])
	{
		CSophia* sophia = INSTANCE_SOPHIA;
		int frameID = sophia->currentAni->GetCurrentFrame();
		if (sophia->currentAni->GetCurrentFrame() > -1)
		{
			RECT r = sophia->currentAni->GetFrameRect(frameID);
			sophia->y_render = sophia->y + SOPHIA_SMALL_BBOX_HEIGHT - (r.bottom - r.top);
		}
	}
	HandleKeyboard();
	
}

void StateDead::HandleKeyboard()
{

	CSophia* sophia = INSTANCE_SOPHIA;

	if (_KEYCODE[DIK_R])
	{
		sophia->Revival();
	
	}
}

StateDead::~StateDead()
{
}
