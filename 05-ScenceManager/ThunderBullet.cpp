#include "ThunderBullet.h"

ThunderBullet::ThunderBullet(float _start_x, float _start_y)
{
	this->start_x = _start_x;
	this->start_y = _start_y;
	isMove = true;
	isDone = false;
	bulletDame = 1;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(17));
}

void ThunderBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	BulletObject::Update(dt, coObjects);
	if (isDone) return;
}

void ThunderBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDone)
	{
		if (animation_set->at(0)->GetCurrentFrame() == 0)
		{
			left = start_x;
			top = start_y;
			right = start_x + 15;
			bottom = start_y + 16;
			
		}
		if (animation_set->at(0)->GetCurrentFrame() == 1)
		{
			left = start_x;
			top = start_y;
			right = start_x + 15;
			bottom = start_y + 16*2;
		}
		if (animation_set->at(0)->GetCurrentFrame() == 2)
		{
			left = start_x;
			top = start_y;
			right = start_x + 15;
			bottom = start_y + 16*2;
		}
		if (animation_set->at(0)->GetCurrentFrame() == 3)
		{
			left = start_x;
			top = start_y - 16;
			right = start_x + 15;
			bottom = start_y + 16 * 4;
		}
		if (animation_set->at(0)->GetCurrentFrame() == 5)
		{
			left = start_x;
			top = start_y - 32;
			right = start_x + 15;
			bottom = start_y + 16 * 4;
		}
	
	}
}

void ThunderBullet::Render()
{
	int ani = 0;
	int alpha = rand() % (255 + 1) + 0;
	if (isDone) return;
	animation_set->at(0)->RenderThreeBullet(x, y,alpha);
	if (animation_set->at(0)->GetCurrentFrame() == animation_set->at(0)->GetLastFrame())
	{
		isDone = true;
	}
	RenderBoundingBox(x,y);
	
}
