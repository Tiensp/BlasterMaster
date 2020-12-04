#include "Eyeballs.h"
#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Sophia.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"
#include "Brick.h"
CEyeballs::CEyeballs(float x, float y, LPGAMEOBJECT player)
{
	SetState(EYEBALL_ANI_WALKING);
	this->x = x;
	this->y = y;
	this->target = player;

	hp = 1;

	objTag = ENEMY;
	objType = EYEBALLS;

}

int CEyeballs::RandomNXNY(int min, int max)
//the parameters must be min = 3, max = 3;
{
	int x = rand() % min + max;
	return x;
}

void CEyeballs::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDoneDeath)
	{
		left = x;
		top = y;
		right = x + EYEBALL_BBOX_WIDTH;
		bottom = y + EYEBALL_BBOX_HEIGHT;

		/*if (state == INSECT_STATE_DIE)
			bottom = y + INSECT_BBOX_HEIGHT_DIE;
		else
			bottom = y + INSECT_BBOX_HEIGHT;*/
	}
	else return;
}

void CEyeballs::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

		timer += interval;

		if (timer == timeChangeState)
		{
			if (this->GetState() == EYEBALL_ANI_WALKING)
			{
				this->SetState(EYEBALL_ANI_IDLE);
				timer = 0;
			}
			else if (this->GetState() == EYEBALL_ANI_IDLE)
			{
				this->SetState(EYEBALL_ANI_WALKING);	
				timer = 0;
			}
		}
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


		//x += min_tx * dx + nx * 0.4f;  //cập nhật lại vị trí x
		//y += min_ty * dy + ny * 0.4f;	// cập nhật lại vị trí y  để tránh bị hụt xuống

		// block every object first!
		{
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<CBrick*>(e->obj)) // if e->obj is Goomba 
				{

					CBrick* brick = dynamic_cast<CBrick*>(e->obj);

					// jump on top >> kill Goomba and deflect a bit 
				}
				if (e->obj->objTag == Player)
				{
					x += dx;
					y += dy;
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


void CEyeballs::Render()
{
	int ani = EYEBALL_ANI_WALKING;

	if (isDoneDeath) return;
	if (hp == 0) isDeath = true;

	if (isDeath)
	{
		ani = EYEBALL_ANI_DEATH;
		animation_set->at(ani)->Render(x, y);
		if (animation_set->at(ani)->GetCurrentFrame() == 3)
		{
			isDoneDeath = true;
		}
		return;
	}

	if (counter == 0)
	{
		ani = EYEBALL_ANI_WALKING;
		animation_set->at(ani)->Render(x, y);
		if (animation_set->at(ani)->GetCurrentFrame() == 6)
		{
			counter++;
		}
	}
	else if (counter == 1)
	{
		ani = EYEBALL_ANI_IDLE;
		animation_set->at(ani)->Render(x, y);
		if (animation_set->at(ani)->GetCurrentFrame() == 6)
		{
			counter++;
		}
	}
	else if (counter == 2)
	{
		counter = 0;
	}

	animation_set->at(ani)->Render(x, y);
	
	RenderBoundingBox();
}

void CEyeballs::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case EYEBALL_ANI_WALKING:

		nx = rand() % 2 + 1;
		ny = rand() % 5 + 4;

		if (nx == 1)
		{
			vx = EYEBALL_WALKING_SPEED_X;
		}
		else if (nx == 2)
		{
			vx = -EYEBALL_WALKING_SPEED_X;
		}
		if (ny == 4)
		{
			vy = EYEBALL_WALKING_SPEED_Y;
		}
		else if (ny == 5)
		{
			vy = -EYEBALL_WALKING_SPEED_Y;
		}
		break;
	case EYEBALL_ANI_IDLE:
		vx = 0;
		vy = 0;
		nx = 0;
		ny = 0;
		break;
	case EYEBALL_ANI_DEATH:
		vx = 0;
		nx = 0;
		vy = 0;
		ny = 0;
		break;
	}
}
