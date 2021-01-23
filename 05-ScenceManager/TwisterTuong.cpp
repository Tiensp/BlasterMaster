#include "TwisterTuong.h"
#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Sophia.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"
#include "Brick.h"

CTWISTERTUONG::CTWISTERTUONG(float x, float y, LPGAMEOBJECT player)
{
	SetState(TWISTERTUONG_ANI_WALKING_LEFT);
	this->x = x;
	this->y = y;
	this->target = player;

	hp = 3;

	objTag = ENEMY;
	objType = TWISTERTUONG;
};

void CTWISTERTUONG::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDoneDeath)
	{
		left = x;
		top = y;
		right = x + TWISTERTUONG_BBOX_WIDTH;
		bottom = y + TWISTERTUONG_BBOX_HEIGHT;
	}
	else return;
};

void CTWISTERTUONG::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::Update(dt, coObjects);
	//Attack();
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)  //nếu không có va chạm, update bình thường
	{
		x += dx;
		y += dy;
	}
	else //có va chạm
	{
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);


		x += min_tx * dx + nx * 0.4f;  //cập nhật lại vị trí x
		y += min_ty * dy + ny * 0.4f;	// cập nhật lại vị trí y  để tránh bị hụt xuống
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

							this->SetState(TWISTERTUONG_ANI_WALKING_RIGHT);

						}
						else if (e->nx < 0)
						{

							this->SetState(TWISTERTUONG_ANI_WALKING_LEFT);

						}

					}
				}
				else
				{
					x += dx;
					y += dy;
				}
			}
		}
	}
};
void CTWISTERTUONG::Render()
{
	int ani = TWISTERTUONG_ANI_WALKING_RIGHT;
	if (isDoneDeath) return;
	if (hp <= 0) isDeath = true;
	if (isDeath)
	{
		ani = TWISTERTUONG_ANI_DEATH;
		animation_set->at(ani)->Render(x, y);
		if (animation_set->at(ani)->GetCurrentFrame() == 2)
		{
			isDoneDeath = true;
		}
		return;
	}
	else {
		if (nx > 0 & ny < 0)
		{
			if (vx > 0 & vy > 0)
			{
				ani = TWISTERTUONG_ANI_WALKING_RIGHT;
			}
		}
		else if (nx < 0 & ny > 0)
		{
			if (vx < 0 & vy < 0)
			{
				ani = TWISTERTUONG_ANI_WALKING_LEFT;
			}
		}
	};

	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox(x, y);
};
void CTWISTERTUONG::SetState(int state)
	{
		CGameObject::SetState(state);
		switch (state)
		{
		case TWISTERTUONG_ANI_WALKING_LEFT:
				vx = TWISTERTUONG_SPEED_X;
				nx = 1;
				vy = -TWISTERTUONG_SPEED_Y;
				ny = 1;
			break;
		case TWISTERTUONG_ANI_WALKING_RIGHT:
				vx = -TWISTERTUONG_SPEED_X;
				nx = -1;
				vy = TWISTERTUONG_SPEED_Y;
				ny = -1;
			break;


		};
	};
