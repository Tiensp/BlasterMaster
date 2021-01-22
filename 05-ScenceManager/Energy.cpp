#include "Energy.h"

Energy::Energy(int _energy)
{
	currentEnergy = _energy;
	LPANIMATION_SET Energy_aniSet = CAnimationSets::GetInstance()->Get(500);
	Energy_ani = Energy_aniSet->at(ANISET_HP);
}

void Energy::Update()
{
	if (_ACTIVE[SOPHIA]) {
		currentEnergy = INSTANCE_SOPHIA->GetEnergy();
	}
	/*else if (_ACTIVE[JASON]) {
		currentHP = playerSmall->health;
	}*/
	else if (_ACTIVE[BIG_JASON]) {
		currentEnergy = INSTANCE_BIGJASON->GetEnergy();
	}
}
void Energy::Render(float xHUD, float yHUD)
{
	//Nếu hết máu thì ngưng không render nữa
	if (currentEnergy <= 0)
		return;
	else {
		/*
			Thanh HUD có độ dài 8 ô, mỗi ô có height là 5 và width là 10
			Phần viền cạnh của HUD có độ dày 1
			Vì vậy ta sẽ render mỗi 'cục' máu có height 4 width 8 và bắt đầu render
			từ vị trí top-left của mỗi ô
			-> Vị trí đầu tiên cần render là vị trí (5 * 7) + 1(viền trên) = 36
				và trừ 5 cho vị trí render mỗi 'cục' máu tiếp theo.
		*/
		for (int i = 0; i < currentEnergy; i++)
		{
			Energy_ani->RenderWithoutTrans(xHUD + 1, yHUD + 36 - i * 5);
		}
	}
}

Energy::~Energy()
{
}

