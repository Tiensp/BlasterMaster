#pragma once
#include "State.h"
#include "Sophia.h"
#include "Jason.h"

class StateWALKINGGunUP : public CState
{
public:
	StateWALKINGGunUP();
	void Update();
	void HandleKeyboard();

	~StateWALKINGGunUP();

};

