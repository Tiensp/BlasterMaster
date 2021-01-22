#pragma once
#include "State.h"
#include "Sophia.h"
#include "Jason.h"
#include "BigJason.h"
class StateDead : public CState
{
public:
	StateDead();
	void Update() ;
	void HandleKeyboard() ;

	~StateDead();
};

