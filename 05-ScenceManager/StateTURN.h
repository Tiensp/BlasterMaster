#pragma once
#include "State.h"
#include "Sophia.h"
#include "Jason.h"

class StateTURN : public CState
{
public:
	StateTURN();
	void Update();
	void HandleKeyboard();

	~StateTURN();

};

