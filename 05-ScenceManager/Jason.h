#pragma once
#include "GameObject.h"
#include "State.h"
class CJason : public CGameObject, public CState 
{
	int level;
	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Sophia at scene
	float start_y;

public:
	CJason(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	virtual void KeyState();
	virtual void OnKeyDown(int keycode);
	virtual void OnKeyUp(int keycode);

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
};

