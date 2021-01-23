#pragma once
#include "State.h"
#include "Sophia.h"
#include "Jason.h"

class StateFALLGunUP : public CState
{
public:
	StateFALLGunUP();
	void Update();
	void HandleKeyboard();

	~StateFALLGunUP();

};

