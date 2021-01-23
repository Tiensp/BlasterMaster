#include "StateIDLEGunUP.h"
#include "StateTURN.h"
#include "StateIDLE.h"
#include "StateWALKING.h"
#include "StateLOWEREDGun.h"
#include "StateWALKINGGunUP.h"

StateIDLEGunUP::StateIDLEGunUP()
{
	

	CSophia* sophia = INSTANCE_SOPHIA;
	sophia->renderFrame = true;
	sophia->SetIsWalking(false);
	sophia->SetIsJumping(false);
	sophia->SetIsFalling(false);
	sophia->SetIsRaisedGun(false);
	sophia->SetIsGunUp(true);
	sophia->vx = 0;

	/* 
		Vì Sprite IDLE GUN UP bên phải sẽ có phần tâm xe bị lệch so với tâm xe của 
		các animation giương súng '4' pixel và ngược lại là '3' pixel với 
		các animation giương súng bên trái (số '3' px chắc hơi khó hiểu, xem lại kỹ sprite
		vì sprite bên trái lệch '4' từ chiều đuôi xe tính đến mũi xe NHƯNG lệch 3 px nếu 
		tính từ mũi xe đến đuôi xe.
	*/
	if (sophia->nx > 0)
	{
		sophia->x_render = sophia->x - 4;
		StateName = SOPHIA_IDLE_GUN_UP_RIGHT;
	}
	else
	{
		sophia->x_render = sophia->x + 3;
		StateName = SOPHIA_IDLE_GUN_UP_LEFT;
	}

	RECT r = sophia->animation_set->at(StateName)->GetFrameRect(0);
	sophia->y_render = sophia->y + SOPHIA_SMALL_BBOX_HEIGHT - (r.bottom - r.top);
}

void StateIDLEGunUP::Update()
{
	CSophia* sophia = INSTANCE_SOPHIA;

#pragma region Thay đổi x/y_render
	// Xem lại chú thích y_render ở StateRAISEDGun
	if (sophia->nx > 0 )
		sophia->x_render = sophia->x - 4;
	else
		sophia->x_render = sophia->x + 3;

	if (sophia->currentAni->GetCurrentFrame() > -1)
	{
		RECT r = sophia->currentAni->GetFrameRect(sophia->currentAni->GetCurrentFrame());
		sophia->y_render = sophia->y + SOPHIA_SMALL_BBOX_HEIGHT - (r.bottom - r.top);
	}
	else
	{
		RECT r = sophia->currentAni->GetFrameRect(0);
		sophia->y_render = sophia->y + SOPHIA_SMALL_BBOX_HEIGHT - (r.bottom - r.top);
	}
#pragma endregion

	this->HandleKeyboard();
}

void StateIDLEGunUP::HandleKeyboard()
{
	CSophia* sophia = INSTANCE_SOPHIA;
	if (!sophia->GetIsRaisedGun())
	{
		if (_KEYCODE[DIK_UP])
		{
			if (_KEYCODE[DIK_RIGHT])
			{
				sophia->nx = 1;
				sophia->SwitchState(new StateWALKINGGunUP(), IDLE2WALK);
			}
			else if (_KEYCODE[DIK_LEFT])
			{
				sophia->nx = -1;
				sophia->SwitchState(new StateWALKINGGunUP(), IDLE2WALK);
			}
			else
			{
				sophia->SwitchState(new StateIDLEGunUP(), WALK2IDLE);
			}
			
		}
		else
		{
			sophia->SetIsGunUp(false);
			sophia->SwitchState(new StateLOWEREDGun(), NORMAL_STATE);
			sophia->currentAni->ResetCurrentFrame();
		}
			
		
	}
}

StateIDLEGunUP::~StateIDLEGunUP()
{
}


