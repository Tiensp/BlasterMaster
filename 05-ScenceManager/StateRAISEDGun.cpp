#include "StateRAISEDGun.h"
#include "StateTURN.h"
#include "StateIDLE.h"
#include "StateWALKING.h"
#include "StateIDLEGunUP.h"
#include "StateLOWEREDGun.h"

StateRAISEDGun::StateRAISEDGun()
{
	CSophia* sophia = INSTANCE_SOPHIA;
	sophia->renderFrame = false;
	sophia->SetIsRaisedGun(true);

	if (sophia->nx > 0)
	{
		StateName = SOPHIA_RAISED_GUN_RIGHT;
	}
	else
	{
		StateName = SOPHIA_RAISED_GUN_LEFT;
	}

	/*
		Khi khởi tạo state lần đầu cần đổi lại vị trí Render của Animation
		Vị trí ở đây mình + BBOX height khi đứng yên để lấy được y.Bottom của nhân vật
		Sau đó trừ lấy chiều cao của sprite cần vẽ từ RECT sprite để tìm ra y_render
	*/
	RECT r = sophia->animation_set->at(StateName)->GetFrameRect(0);
	sophia->y_render = sophia->y + SOPHIA_SMALL_BBOX_HEIGHT - (r.bottom - r.top);
}

void StateRAISEDGun::Update()
{
	CSophia* sophia = INSTANCE_SOPHIA;
#pragma region Thay đổi vị trí Render Animation

	/* 
		Cách thay đổi y_render tương tự như trên nhưng có trừ thêm '2' 
		vì trong quá trình vẽ, ngoại trừ frame[0] vẽ đúng còn lại các frame khác
		mặc dù trừ đúng chiều cao trên "lý thuyết" nhưng khi render vẫn bị lệch 
		-> phải trừ thêm '2' pixel nữa :vv 
	*/

	// Nếu currentFrame == -1 thì y_render = y_render của frame đầu tiên (frames[0])
	int frameID = sophia->currentAni->GetCurrentFrame();  
	if (sophia->currentAni->GetCurrentFrame() > -1)
	{
		RECT r = sophia->currentAni->GetFrameRect(frameID);	
		sophia->y_render = sophia->y + SOPHIA_SMALL_BBOX_HEIGHT - (r.bottom - r.top) - 2;
	}
	else
	{
		RECT r = sophia->currentAni->GetFrameRect(0);
		sophia->y_render = sophia->y + SOPHIA_SMALL_BBOX_HEIGHT - (r.bottom - r.top);
	}

#pragma endregion
	this->HandleKeyboard();
}

void StateRAISEDGun::HandleKeyboard()
{
	CSophia* sophia = INSTANCE_SOPHIA;
	if (!sophia->GetIsRaisedGun())
	{
		if (_KEYCODE[DIK_UP])
		{
			sophia->SwitchState(new StateIDLEGunUP(), WALK2IDLE);
		}
		else
		{
			sophia->SwitchState(new StateLOWEREDGun(), NORMAL_STATE);
			sophia->currentAni->ResetCurrentFrame();
		}
			
	}
}

StateRAISEDGun::~StateRAISEDGun()
{
}


