#pragma once
#include "State.h"
#include "Sophia.h"
#include "Jason.h"

class StateFALLTurn : public CState
{
public:
	StateFALLTurn();
	void Update();
	void HandleKeyboard();

	~StateFALLTurn();

};

