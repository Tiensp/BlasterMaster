#include "Enemy.h"

Enemy::Enemy()
{
	
}

Enemy::~Enemy()
{
}
void Enemy::Render()
{
}

void Enemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt, coObjects);
	if (this->hp <= 0) isDeath = true;
	
	
}




