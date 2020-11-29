#include "BulletObject.h"
#include "Sophia.h"
#include "Domes.h"


BulletObject::BulletObject()
{
	this->x = 0;
	this->y = 0;
	isMove = false;
}

BulletObject::~BulletObject()
{
}

void BulletObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;


	
}

void BulletObject::Set_IsMove(const bool& _isMove)
{
	this->isMove = _isMove;
}

void BulletObject::HandleMove(const float& x_border, const float& y_border)
{
	if (x > x_border)
	{
		isMove = false;
	}

}

void BulletObject::Render()
{
	int ani = 0;
}
