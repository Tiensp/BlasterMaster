#pragma once
#include "State.h"
#include "Sophia.h"
#include "Jason.h"

class StateFALL : public CState
{
public:
	StateFALL();
	void Update();
	void HandleKeyboard();

	~StateFALL();

};

