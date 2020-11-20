#pragma once
#include "State.h"
#include "Sophia.h"
#include "Jason.h"

class StateJUMP : public CState
{
public:
	StateJUMP();
	void Update();
	void HandleKeyboard();

	~StateJUMP();

};

