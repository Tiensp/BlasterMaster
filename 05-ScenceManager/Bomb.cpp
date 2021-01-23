#include "Bomb.h"
#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Sophia.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"
#include "Brick.h"
CBomb::CBomb(float x, float y)
{
	SetState(BOMB_ANI_IDLE);
	this->x = x;
	this->y = y;

	hp = 1;

	objTag = ENEMY;
	objType = MINE;

}

void CBomb::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDoneDeath)
	{
		left = x;
		top = y;
		right = x + BOMB_BBOX_WIDTH;
		bottom = y + BOMB_BBOX_HEIGHT;

		/*if (state == SHIP_STATE_DIE)
			bottom = y + SHIP_BBOX_HEIGHT_DIE;
		else
			bottom = y + SHIP_BBOX_HEIGHT;*/
	}
	else return;
}

void CBomb::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//vy += 0.0005f * dt;

	if (bomb_bullet != NULL)
	{
		if (!bomb_bullet->isDone)
		{
			bomb_bullet->Update(dt, coObjects);
		}
		else
		{
			return;
		}
	}

	if (hp <= 0) {

		this->isDeath = true;
		this->SetState(BOMB_ANI_DEAD);

	}


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

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

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		{
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (e->obj->objTag == ENEMY)
				{
					x += dx;
					y += dy;
				}
			}
		}
	}
}


void CBomb::Render()
{
	int ani = BOMB_ANI_IDLE;

	if (isDoneDeath) return;
	if (hp <= 0) isDeath = true;

	if (isDeath)
	{
		ani = BOMB_ANI_DEAD;

		changeState++;

		animation_set->at(ani)->Render(x, y);

		if (bomb_bullet == NULL) {

			bomb_bullet = new BombBullet(this->x, this->y);
			bomb_bullet->Set_bullet_dir(-1);
			bomb_bullet->Set_IsMove(true);
		}

		if (changeState == 15 && bomb_bullet != NULL) {
			bomb_bullet->Set_bullet_dir(1);
		}

		if (animation_set->at(ani)->GetCurrentFrame() == 3 && bomb_bullet->isDone)
		{
			isDoneDeath = true;
		}

	}

	if (bomb_bullet != NULL)
	{
		bomb_bullet->Render();
	}

	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox(x, y);
}


void CBomb::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BOMB_ANI_IDLE:
		vx = 0;
		vy = 0;
		nx = 0;
		ny = 0;
		break;
	case BOMB_ANI_DEAD:
		vx = 0;
		vy = 0;
		nx = -1;
		ny = 0;
		break;
	}
}