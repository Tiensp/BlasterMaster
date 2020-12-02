#include "Ship.h"
#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Sophia.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"
#include "Brick.h"
CShip::CShip(float x, float y, LPGAMEOBJECT player)
{
	SetState(SHIP_ANI_WALKING_LEFT);
	this->x = x;
	this->y = y;
	this->target = player;

	objTag = ENEMY;
	objType = SHIPS;

}

void CShip::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + SHIP_BBOX_WIDTH;

	if (state == SHIP_STATE_DIE)
		bottom = y + SHIP_BBOX_HEIGHT_DIE;
	else
		bottom = y + SHIP_BBOX_HEIGHT;
}

void CShip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	//DebugOut(L"golumnvX: %f, golumnvY: %f\n", vx, vy);
	CGameObject::Update(dt, coObjects);
	//DebugOut(L"golumnvX: %f, golumnvY: %f\n", vx, vy);

	//DebugOut(L"golumnvX: %f, golumnvY: %f\n", target->nx, this->nx);


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	//nếu không chết thì kiểm tra toàn bộ va chạm với các đối tượng khác
	CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed

	// No collision occured, proceed normally

	if (coEvents.size() == 0)  //nếu không có va chạm, update bình thường
	{
		x += dx;
		y += dy;

		Attack();
	}
	else //có va chạm
	{
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);  // sắp xếp lại các sự kiện va chạm đầu tiên theo trục x, y 

		// how to push back Sophia if collides with a moving objects, what if Sophia is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 


		x += min_tx * dx + nx * 0.4f;  //cập nhật lại vị trí x
		y += min_ty * dy + ny * 0.4f;	// cập nhật lại vị trí y  để tránh bị hụt xuống

		// block every object first!
		{
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<CBrick*>(e->obj)) // if e->obj is Goomba 
				{
					isAttack = false;

					CBrick* brick = dynamic_cast<CBrick*>(e->obj);

					// jump on top >> kill Goomba and deflect a bit 
					if (e->nx != 0)
					{
						if (e->nx > 0)
						{
							if (this->nx < 0)
							{
								this->SetState(SHIP_ANI_WALKING_RIGHT);
							}
						}
						else if (e->nx < 0)
						{
							if (this->nx > 0)
							{
								this->SetState(SHIP_ANI_WALKING_LEFT);
							}
						}

					}
					/*else if (e->ny != 0)
					{
						if (e->ny > 0)
						{
							if (this->GetState() == SKULL_ANI_COLLISION_LEFT)
							{
								this->SetState(SKULL_ANI_COLLISION_LEFT);
							}
						}
					}*/
				}
				if (e->obj->objTag == ENEMY)
				{
					x += dx;
					y += dy;
				}
			}
		}



	}
}

void CShip::Attack()
{

	if (abs(this->x - target->x) <= 30)
	{
		isAttack = true;
		if (this->GetState() == SHIP_ANI_WALKING_LEFT)
		{
			this->SetState(SHIP_ANI_ATTACKING_LEFT);
		}
		else if (this->GetState() == SHIP_ANI_WALKING_RIGHT)
		{
			this->SetState(SHIP_ANI_ATTACKING_RIGHT);
		}
	}
	else
	{
		isAttack = false;
		if (this->nx > 0)
		{
			this->SetState(SHIP_ANI_WALKING_RIGHT);
		}
		else if (this->nx < 0)
		{
			this->SetState(SHIP_ANI_WALKING_LEFT);
		}
	}

}



void CShip::Render()
{
	int ani = SHIP_ANI_WALKING_LEFT;

	if (isAttack)
	{
		if (nx > 0)
		{
			ani = SHIP_ANI_ATTACKING_RIGHT;
		}
		else if (nx < 0)
		{
			ani = SHIP_ANI_ATTACKING_LEFT;
		}
	}
	else
	{
		if (nx > 0)
		{
			if (vx > 0)
			{
				ani = SHIP_ANI_WALKING_RIGHT;
			}
		}
		else if (nx < 0)
		{
			if (vx < 0)
			{
				ani = SHIP_ANI_WALKING_LEFT;
			}
		}
	}

	DebugOut(L"ani: %d\n", ani);

	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

//void CSkull::flowPlayer(LPGAMEOBJECT player)
//{
//	if (abs(this->x - player->x) <= 100)
//	{
//		if (this->x - player->x <= 0)
//		{
//			this->nx = -1;
//		}
//		else
//		{
//			this->nx = 1;
//		}
//	}
//
//}



void CShip::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SHIP_STATE_DIE:
		y += SHIP_BBOX_HEIGHT - SHIP_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case SHIP_ANI_WALKING_LEFT:
		vx = -SHIP_WALKING_SPEED;
		nx = -1;
		vy = 0;
		ny = 0;
		break;
	case SHIP_ANI_WALKING_RIGHT:
		vx = SHIP_WALKING_SPEED;
		nx = 1;
		vy = 0;
		ny = 0;
		break;
	case SHIP_ANI_ATTACKING_LEFT:
		vx = -SHIP_WALKING_SPEED;
		nx = -1;
		vy = 0;
		ny = 0;
		break;
	case SHIP_ANI_ATTACKING_RIGHT:
		vx = SHIP_WALKING_SPEED;
		nx = 1;
		vy = 0;
		ny = 0;
		break;
	}
}
