#pragma once
#include "State.h"
#include "Sophia.h"
#include "Jason.h"

class StateRAISEDGun : public CState
{
public:
	StateRAISEDGun();
	void Update();
	void HandleKeyboard();

	~StateRAISEDGun();

};

