#include "BulletObject.h"
#include "Sophia.h"
#include "Brick.h"
#include "Enemy.h"



void BulletObject::Set_IsMove(const bool& _isMove)
{
	this->isMove = _isMove;
}

void BulletObject::HandleMove(const float x_border, const float y_border)
{
	if (x > start_x + x_border || x < start_x - x_border || y < start_y - y_border)
	{
		isMove = false;
		isDone = true;
	}
}

