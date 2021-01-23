#include "HUDEnergy.h"

HUDEnergy::HUDEnergy()
{
	LPANIMATION_SET HUD_aniSet = CAnimationSets::GetInstance()->Get(501);
	HUD_ani = HUD_aniSet->at(ANISET_HP_BAR);
	if (_ACTIVE[SOPHIA])
	{
		playerEnergy = new Energy(INSTANCE_SOPHIA->GetEnergy());
	}
	else if (_ACTIVE[BIG_JASON])
	{
		playerEnergy = new Energy(INSTANCE_BIGJASON->GetEnergy());
	}
}

void HUDEnergy::Update()
{
	playerEnergy->Update();
}

void HUDEnergy::Render()
{
	D3DXVECTOR2 hudPos = CCamera::GetInstance()->GetCamPos();
	float xHUD = hudPos.x + 16;
	float yHUD = hudPos.y + 100;
	HUD_ani->Render(xHUD, yHUD);
	playerEnergy->Render(xHUD, yHUD);
}

HUDEnergy::~HUDEnergy()
{
}
