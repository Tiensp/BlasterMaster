#pragma once
#include "GameObject.h"
class Enemy : public CGameObject
{
protected:
	LPGAMEOBJECT target;
	bool isDeath;
public:
	Enemy();
	~Enemy();
	virtual void Render() = 0 ;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects =NULL) = 0;
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) = 0;

};


