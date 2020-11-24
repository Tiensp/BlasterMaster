#pragma once
#include "State.h"
#include "Sophia.h"
#include "Jason.h"
#include "BigJason.h"

class StateIDLE : public CState
{
public:
	StateIDLE();
	void Update();
	void HandleKeyboard();

	~StateIDLE();

};

