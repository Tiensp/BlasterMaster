#pragma once
#include "GameObject.h"
class Enemy : public CGameObject
{
protected:
	LPGAMEOBJECT target;
	bool isDeath;
	bool isAttack;
	int hp;
public:
	Enemy();
	~Enemy();
	virtual void Render() = 0 ;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Set_hp(int dameBullet) { this->hp -= dameBullet; }
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) = 0;
	bool GetIsDeath() { return isDeath; }
	bool SetIsDeath(bool isDeath1) { return this->isDeath = isDeath1; }
	
};


