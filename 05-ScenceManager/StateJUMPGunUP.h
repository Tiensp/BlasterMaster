#pragma once
#include "State.h"
#include "Sophia.h"
#include "Jason.h"

class StateJUMPGunUP : public CState
{
public:
	StateJUMPGunUP();
	void Update();
	void HandleKeyboard();

	~StateJUMPGunUP();

};

