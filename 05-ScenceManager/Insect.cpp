#include "Insect.h"
#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Sophia.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"
#include "Brick.h"
CInsect::CInsect(float x, float y, LPGAMEOBJECT player)
{
	SetState(INSECT_ANI_DROP_DOWN);
	this->x = x;
	this->y = y;
	this->target = player;

	hp = 2;

	objTag = ENEMY;
	objType = INSECTS;

}

void CInsect::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDoneDeath)
	{
		left = x;
		top = y;
		right = x + INSECT_BBOX_WIDTH;
		bottom = y + INSECT_BBOX_HEIGHT;
	}
	else return;
}

void CInsect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	Enemy::Update(dt, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	timer += 10;

	if (timer == 0) {
		this->SetState(INSECT_ANI_DROP_DOWN);
	}
	else if (timer == 300)
	{
		if (this->nx == 1) {
			if (this->GetState() == INSECT_ANI_DROP_DOWN) {
				this->SetState(INSECT_ANI_WALKING_RIGHT_UP);
			}
		}
		else if (this->nx == -1) {
			if (this->GetState() == INSECT_ANI_DROP_DOWN) {
				this->SetState(INSECT_ANI_WALKING_LEFT_UP);
			}
		}

		timer = 300;
	}
	else if (timer == 650)
	{
		if (this->GetState() == INSECT_ANI_WALKING_LEFT_UP)
		{
			this->SetState(INSECT_ANI_WALKING_LEFT_DOWN);
		}
		else if (this->GetState() == INSECT_ANI_WALKING_RIGHT_UP)
		{
			this->SetState(INSECT_ANI_WALKING_RIGHT_DOWN);
		}

		timer = 650;
	}
	else if (timer == 950) {
		if (this->GetState() == INSECT_ANI_WALKING_LEFT_DOWN) {
			this->SetState(INSECT_ANI_WALKING_LEFT_UP);
		}
		else if (this->GetState() == INSECT_ANI_WALKING_RIGHT_DOWN) {
			this->SetState(INSECT_ANI_WALKING_RIGHT_UP);
		}

		timer = 100;
	}


	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else //có va chạm
	{
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);


		x += min_tx * dx + nx * 0.4f;  //cập nhật lại vị trí x
		y += min_ty * dy + ny * 0.4f;	// cập nhật lại vị trí y  để tránh bị hụt xuống

		// block every object first!
		{
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<CBrick*>(e->obj))
				{

					CBrick* brick = dynamic_cast<CBrick*>(e->obj);

					if (e->nx != 0)
					{
						if (e->nx > 0)
						{
							if (this->ny > 0)
							{
								this->SetState(INSECT_ANI_WALKING_RIGHT_DOWN);
							}
							else if (this->ny < 0)
							{
								this->SetState(INSECT_ANI_WALKING_RIGHT_UP);
							}
						}
						else if (e->nx < 0)
						{
							if (this->ny > 0)
							{
								this->SetState(INSECT_ANI_WALKING_LEFT_DOWN);
							}
							else if (this->ny < 0)
							{
								this->SetState(INSECT_ANI_WALKING_LEFT_UP);
							}
						}

					}
					else if (e->ny != 0)
					{
						if (e->ny > 0)
						{
							if (this->nx > 0)
							{
								this->SetState(INSECT_ANI_WALKING_RIGHT_DOWN);
							}
							else if (this->nx < 0)
							{
								this->SetState(INSECT_ANI_WALKING_LEFT_DOWN);
							}
						}
						else if (e->ny < 0)
						{
							if (this->nx > 0)
							{
								this->SetState(INSECT_ANI_WALKING_RIGHT_UP);
							}
							else if (this->nx < 0)
							{
								this->SetState(INSECT_ANI_WALKING_LEFT_UP);
							}
						}
					}
				}
				else {
					x += dx;
					y += dy;
				}
			}
		}
	}
}

void CInsect::Render()
{
	int ani = INSECT_ANI_DROP_DOWN;

	if (isDoneDeath) return;
	if (hp <= 0) isDeath = true;

	if (isDeath)
	{
		ani = INSECT_ANI_DEATH;
		animation_set->at(ani)->Render(x, y);
		if (animation_set->at(ani)->GetCurrentFrame() == 3)
		{
			isDoneDeath = true;
		}
		return;
	}

	if (vx > 0 && vy > 0)
	{
		ani = INSECT_ANI_WALKING_RIGHT_DOWN;
	}
	else if (vx > 0 && vy < 0)
	{
		ani = INSECT_ANI_WALKING_RIGHT_UP;
	}
	else if (vx < 0 && vy > 0)
	{
		ani = INSECT_ANI_WALKING_LEFT_DOWN;
	}
	else if (vx < 0 && vy < 0)
	{
		ani = INSECT_ANI_WALKING_LEFT_UP;
	}

	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox(x,y);
}


void CInsect::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case INSECT_STATE_DIE:
		y += INSECT_BBOX_HEIGHT - INSECT_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case INSECT_ANI_DROP_DOWN:
		vx = 0;
		nx = 1;
		vy = INSECT_JUMPING_SPEED;
		ny = -1;
		break;
	case INSECT_ANI_WALKING_RIGHT_UP:
		vx = INSECT_WALKING_SPEED;
		nx = 1;
		vy = -INSECT_JUMPING_SPEED;
		ny = -1;
		break;
	case INSECT_ANI_WALKING_RIGHT_DOWN:
		vx = INSECT_WALKING_SPEED;
		nx = 1;
		vy = INSECT_JUMPING_SPEED;
		ny = 1;
		break;
	case INSECT_ANI_WALKING_LEFT_UP:
		vx = -INSECT_WALKING_SPEED;
		nx = -1;
		vy = -INSECT_JUMPING_SPEED;
		ny = -1;
		break;
	case INSECT_ANI_WALKING_LEFT_DOWN:
		vx = -INSECT_WALKING_SPEED;
		nx = -1;
		vy = INSECT_JUMPING_SPEED;
		ny = 1;
		break;
	}
}
