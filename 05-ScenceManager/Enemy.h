#pragma once
#include "GameObject.h"
class Enemy : public CGameObject
{
public:
	Enemy();
	~Enemy();
	virtual void Render() = 0 ;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) = 0;
};

