#pragma once
#include "GameObject.h"
#include "Item.h"

class Enemy : public CGameObject
{
protected:
	LPGAMEOBJECT target;
	bool isDeath;
	bool isAttack;
	int hp;
	int typeItem;
	CItem* Item;
	//bool isDone;
public:
	Enemy();
	~Enemy();
	virtual void Render() = 0 ;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Set_hp(int dameBullet) { this->hp -= dameBullet; }
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) = 0;
	bool GetIsDeath() { return isDeath; }
	
};


