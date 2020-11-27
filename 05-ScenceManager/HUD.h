#pragma once
#include "GameObject.h"
#include "HP.h"
#include "Sophia.h"
#include "Jason.h"
#include "BigJason.h"
#include "Animations.h"
#include "Camera.h"

using namespace std;

class HUD
{
	HP* playerHP;
	LPANIMATION HUD_ani;
public:
	HUD();
	void Update();
	void Render();
	~HUD();
};
