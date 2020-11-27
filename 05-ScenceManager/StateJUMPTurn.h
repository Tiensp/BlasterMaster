#pragma once
#include "State.h"
#include "Sophia.h"
#include "Jason.h"

class StateJUMPTurn : public CState
{
public:
	StateJUMPTurn();
	void Update();
	void HandleKeyboard();

	~StateJUMPTurn();

};

