#pragma once
#include "State.h"
#include "Sophia.h"
#include "Jason.h"

class StateLOWEREDGun : public CState
{
public:
	StateLOWEREDGun();
	void Update();
	void HandleKeyboard();

	~StateLOWEREDGun();

};

