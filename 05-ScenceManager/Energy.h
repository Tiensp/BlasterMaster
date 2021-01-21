#pragma once
#include "GameDefine.h"
#include "Animations.h"
#include "Sophia.h"
#include "Jason.h"
#include "BigJason.h"

class Energy
{
	int currentEnergy;
	LPANIMATION Energy_ani;
public:
	Energy(int _energy);
	void Update();
	void Render(float xHUD, float yHUD);
	~Energy();

};