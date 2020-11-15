#pragma once
class CState
{
public: 
	virtual void Access() = 0;	//sự kiện kích hoạt state
	virtual void Process() = 0;
	virtual void Exit() = 0;	//sự kiện thoát state
};

