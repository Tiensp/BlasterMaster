#pragma once
#include "GameDefine.h"

class CState
{
public: 
	~CState() {}
	virtual void HandleKeyboard() = 0;
	virtual void Update() = 0;

	int StateName;
};

