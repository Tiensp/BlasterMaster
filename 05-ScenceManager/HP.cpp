#include "HP.h"

HP::HP(int _hp)
{
	currentHP = _hp;
	LPANIMATION_SET HP_aniSet = CAnimationSets::GetInstance()->Get(Health);
	HP_ani = HP_aniSet->at(ANISET_HP);
}

void HP::Update()
{
	if (_ACTIVE[SOPHIA]) {
		currentHP = CSophia::GetInstance()->GetHealth();
	}
	/*else if (_ACTIVE[JASON]) {
		currentHP = playerSmall->health;
	}
	else if (_ACTIVE[BIG_JASON]) {
		currentHP = 
	}*/
}

void HP::Render(float xHUD, float yHUD)
{
	//Nếu hết máu thì ngưng không render nữa
	if (currentHP <= 0)
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
		for (int i = 0; i < currentHP; i++)
		{
			HP_ani->Render(xHUD + 1, yHUD + 36 - i * 5);
		} 
	}
}

HP::~HP()
{
}
