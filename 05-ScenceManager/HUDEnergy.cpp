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
	HUD_ani->RenderWithoutTrans(16, 80);
	playerEnergy->Render(16, 80);
}

HUDEnergy::~HUDEnergy()
{
}
