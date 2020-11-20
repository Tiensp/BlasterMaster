#pragma once
#include "State.h"
#include "Sophia.h"
#include "Jason.h"

class StateIDLEGunUP : public CState
{
public:
	StateIDLEGunUP();
	void Update();
	void HandleKeyboard();

	~StateIDLEGunUP();

};

