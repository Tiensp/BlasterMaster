#pragma once
#include "State.h"
#include "Sophia.h"
#include "Jason.h"

class StateWALKING : public CState
{
public:
	StateWALKING();
	void Update();
	void HandleKeyboard();

	~StateWALKING();

};

