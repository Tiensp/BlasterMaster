#include "Teleporters.h"
#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Sophia.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"
#include "Brick.h"
CTeleporter::CTeleporter(float x, float y, LPGAMEOBJECT player)
{
	SetState(TELEPORTER_ANI_GRAY_MODE_ON);
	this->x = x;
	this->y = y;
	this->target = player;

	hp = 3;

	objTag = ENEMY;
	objType = TELEPORTERS;

}

void CTeleporter::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDoneDeath)
	{
		left = x;
		top = y;
		right = x + TELEPORTER_BBOX_WIDTH;
		bottom = y + TELEPORTER_BBOX_HEIGHT;

		/*if (state == INSECT_STATE_DIE)
			bottom = y + INSECT_BBOX_HEIGHT_DIE;
		else
			bottom = y + INSECT_BBOX_HEIGHT;*/
	}
	else return;
}

void CTeleporter::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt, coObjects);



	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)  //nếu không có va chạm, update bình thường
	{
		timer += interval;

		if (timer == 200)
		{
			if (this->GetState() == TELEPORTER_ANI_GRAY_MODE_ON)
			{
				this->SetState(TELEPORTER_ANI_GRAY_MODE_OFF);
			}
			else if (this->GetState() == TELEPORTER_ANI_TELEPORT)
			{
				this->SetState(TELEPORTER_ANI_GRAY_MODE_ON);
			}
			timer = 200;
		}

		else if (timer == 800)
		{
			
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

int CTeleporter::RandomPosition(int a, int b)
{
	srand(time(NULL));

	int r = rand() % 2;
	if (r == 0)
		return a;
	else
		return b;
}

void CTeleporter::Render()
{
	int ani = TELEPORTER_ANI_GRAY_MODE_ON;

	if (isDoneDeath) return;
	if (hp == 0) isDeath = true;

	if (isDeath)
	{
		ani = TELEPORTER_ANI_DEATH;
		animation_set->at(ani)->Render(x, y);
		if (animation_set->at(ani)->GetCurrentFrame() == 3)
		{
			isDoneDeath = true;
		}
		return;
	}

	if (vy == -1)
	{
		ani = TELEPORTER_ANI_GRAY_MODE_OFF;
	}
	if (vy == -2)
	{
		ani = TELEPORTER_ANI_TELEPORT;
	}

	animation_set->at(ani)->Render(x, y);

	DebugOut(L"ani%d\n", ani);
	DebugOut(L"state%d\n", this->GetState());


	//RenderBoundingBox();
}

void CTeleporter::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case TELEPORTER_ANI_GRAY_MODE_ON:
		vx = 0;
		nx = 0;
		vy = 0;
		ny = 0;
		break;
	case TELEPORTER_ANI_GRAY_MODE_OFF:
		vx = 0;
		nx = 0;
		vy = -1;
		ny = 0;
		break;
	case TELEPORTER_ANI_TELEPORT:
		vx = 0;
		nx = 0;
		vy = -2;
		ny = 0;
		break;
	case TELEPORTER_ANI_DEATH:
		vx = 0;
		nx = 0;
		vy = 0;
		ny = 0;
		break;
	}
}
