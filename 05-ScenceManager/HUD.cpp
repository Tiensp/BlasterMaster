#include "HUD.h"

HUD::HUD()
{
	LPANIMATION_SET HUD_aniSet = CAnimationSets::GetInstance()->Get(HealthBar);
	HUD_ani = HUD_aniSet->at(ANISET_HP_BAR);
	if (_ACTIVE[SOPHIA])
	{
		playerHP = new HP(INSTANCE_SOPHIA->GetHealth());
	}
	else if (_ACTIVE[BIG_JASON])
	{
		playerHP = new HP(INSTANCE_BIGJASON->GetHealth());
	}
}

void HUD::Update()
{
	playerHP->Update();
}

void HUD::Render()
{
	D3DXVECTOR2 hudPos = CCamera::GetInstance()->GetCamPos();
	float xHUD = hudPos.x + 16;
	float yHUD = hudPos.y + 160;
	HUD_ani->Render(xHUD, yHUD);
	playerHP->Render(xHUD, yHUD);
}

HUD::~HUD()
{
}
