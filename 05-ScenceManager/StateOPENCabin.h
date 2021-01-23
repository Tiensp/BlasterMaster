#pragma once
#include "State.h"
class StateOPENCabin : public CState
{
public:
	StateOPENCabin();
	void Update();
	void HandleKeyboard();

	~StateOPENCabin();
};

