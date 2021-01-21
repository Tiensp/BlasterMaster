#pragma once
#include "GameObject.h"
#include "Energy.h"
#include "Sophia.h"
#include "Jason.h"
#include "BigJason.h"
#include "Animations.h"
#include "Camera.h"


class HUDEnergy
{
	Energy* playerEnergy;
	LPANIMATION HUD_ani;
public:
	HUDEnergy();
	void Update();
	void Render();
	~HUDEnergy();
};

