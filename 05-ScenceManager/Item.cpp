#include "Item.h"

CItem::CItem(int type)
{
	//this->SetAnimationSet(CAnimationSets::GetInstance()->Get(80));
	this->ItemType = type;
	this->isDone = false;
}

CItem::~CItem()
{
}

void CItem::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDeath)
	{
		left = x;
		top = y;
		right = x + 16;
		bottom = y + 16;
	}
}

void CItem::Render()
{
	int ani;
	if (!isDeath)
	{
		if (ItemType == 0)
		{
			ani = 0;
		}
		else if (ItemType == 1)
		{
			ani = 1;
		}
		else if (ItemType == 2)
		{
			ani = 2;
		}
		else if (ItemType == 3)
		{
			ani = 3;
		}
		else if (ItemType == 4)
		{
			ani = 4;
		}
		animation_set->at(ani)->Render(x, y);
	}
	

	RenderBoundingBox();
}
