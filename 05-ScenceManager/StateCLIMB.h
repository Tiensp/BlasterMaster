#pragma once
#include "State.h"
#include "Sophia.h"
#include "Jason.h"
#include "BigJason.h"
class StateCLIMB : public CState
{
public:
	StateCLIMB();
	void Update();
	void HandleKeyboard();

	~StateCLIMB();
};

