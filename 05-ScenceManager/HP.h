#pragma once
#include "GameDefine.h"
#include "Animations.h"
#include "Sophia.h"
#include "Jason.h"
#include "BigJason.h"

class HP
{
	int currentHP;
	LPANIMATION HP_ani;
public:
	HP(int _hp);
	void Update();
	void Render(float xHUD, float yHUD);
	~HP();

};

