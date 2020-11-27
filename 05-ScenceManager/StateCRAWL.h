#pragma once
#include "State.h"
#include "Sophia.h"
#include "Jason.h"
#include "BigJason.h"

class StateCRAWL : public CState
{
public:
	StateCRAWL();
	void Update();
	void HandleKeyboard();

	~StateCRAWL();

};

