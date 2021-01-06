#include "Cannons.h"
#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Sophia.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"
#include "Brick.h"
CCannon::CCannon(float x, float y, LPGAMEOBJECT player)
{
	SetState(CANNON_ANI_SHOOT_TOP_BOTTOM);
	this->x = x;
	this->y = y;
	this->target = player;

	hp = 3;

	objTag = ENEMY;
	objType = CANNONS;

}

void CCannon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDoneDeath)
	{
		left = x;
		top = y;
		right = x + CANNON_BBOX_WIDTH;
		bottom = y + CANNON_BBOX_HEIGHT;

		/*if (state == INSECT_STATE_DIE)
			bottom = y + INSECT_BBOX_HEIGHT_DIE;
		else
			bottom = y + INSECT_BBOX_HEIGHT;*/
	}
	else return;
}

void CCannon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt, coObjects);

	

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)  //nếu không có va chạm, update bình thường
	{

		timer += interval;

		if (timer == timeChangeState)
		{
			if (this->GetState() == CANNON_ANI_SHOOT_TOP_BOTTOM)
			{
				this->SetState(CANNON_ANI_SHOOT_RIGHT_LEFT);
			}
			else if (this->GetState() == CANNON_ANI_SHOOT_RIGHT_LEFT)
			{
				this->SetState(CANNON_ANI_SHOOT_TOP_BOTTOM);
			}
			timer = 0;
		}
	}
	else //có va chạm
	{
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);  // sắp xếp lại các sự kiện va chạm đầu tiên theo trục x, y 


		//x += min_tx * dx + nx * 0.4f;  //cập nhật lại vị trí x
		//y += min_ty * dy + ny * 0.4f;	// cập nhật lại vị trí y  để tránh bị hụt xuống

		// block every object first!
		{
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (e->obj->objTag == Player)
				{
					x += min_tx * dx + nx * 0.4f;  //cập nhật lại vị trí x
					y += min_ty * dy + ny * 0.4f;	// cập nhật lại vị trí y  để tránh bị hụt xuống
					
					vx = vy = 0;
				}
				if (e->obj->objTag == ENEMY)
				{
					/*x += dx;
					y += dy;*/

					vx = vy = 0;
				}
			}
		}
	}
}


void CCannon::Render()
{
	int ani = CANNON_ANI_SHOOT_TOP_BOTTOM;

	if (isDoneDeath) return;
	if (hp == 0) isDeath = true;

	if (isDeath)
	{
		ani = CANNON_ANI_DEATH;
		animation_set->at(ani)->Render(x, y);
		if (animation_set->at(ani)->GetCurrentFrame() == 3)
		{
			isDoneDeath = true;
		}
		return;
	}

	if (vx > 0)
	{
		ani = CANNON_ANI_SHOOT_RIGHT_LEFT;
	}
	else if (vx < 0)
	{
		ani = CANNON_ANI_SHOOT_TOP_BOTTOM;
	}



	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void CCannon::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case CANNON_ANI_SHOOT_RIGHT_LEFT:
		vx = 0.0001f;
		vy = 0;
		nx = 0;
		ny = 0;
		break;
	case CANNON_ANI_SHOOT_TOP_BOTTOM:
		vx = -0.0001f;
		vy = 0;
		nx = 0;
		ny = 0;
		break;
	case CANNON_ANI_DEATH:
		vx = 0;
		nx = 0;
		vy = 0;
		ny = 0;
		break;
	}
}
