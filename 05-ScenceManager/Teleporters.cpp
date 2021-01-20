#include "Teleporters.h"
#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Sophia.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"
#include "Brick.h"
#include "RockOVH.h"
CTeleporter::CTeleporter(float x, float y, LPGAMEOBJECT player)
{
	SetState(TELEPORTER_ANI_GRAY_MODE_ON);
	this->x = x;
	this->y = y;
	this->target = player;

	hp = 2;

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

	if (hp <= 0)
		isDeath = true;

	timer += 5;

	CheckCollisionWithRock(coObjects);

	if (teleporter_bullet != NULL)
	{
		if (!teleporter_bullet->isDone)
		{
			teleporter_bullet->Update(dt, coObjects);
		}
		else
		{
			teleporter_bullet = NULL;
		}
	}


	if (timer == 1500)
	{
		if (this->GetState() == TELEPORTER_ANI_GRAY_MODE_ON)
		{
			this->SetState(TELEPORTER_ANI_GRAY_MODE_OFF);
		}
		/*else if (this->GetState() == TELEPORTER_ANI_GRAY_MODE_OFF)
		{
			if (teleporter_bullet == NULL)
			{
				teleporter_bullet = new BulletTeleporter(this->x, this->y, this->target);
				teleporter_bullet->SetPosition(this->x + width + 10, this->y + height + 15);
				teleporter_bullet->Set_bullet_dir(this->nx, this->ny);
				teleporter_bullet->Set_IsMove(true);
			}
			this->SetState(TELEPORTER_ANI_GRAY_MODE_ON);
		}*/
		timer = 1500;
	}

	else if (timer == 1550)
	{
		int r = RandomPosition();

		if (this->GetState() == TELEPORTER_ANI_GRAY_MODE_OFF) {

			if (r == 0) {
				this->new_x = this->x + 50;
				this->new_y = this->y;
				this->old_x = this->x;
				this->old_y = this->y;
				this->SetPosition(new_x, new_y);
				this->SetState(TELEPORTER_ANI_TELEPORT);
			}
			else if (r == 1) {
				this->new_x = this->x - 50;
				this->new_y = this->y;
				this->old_x = this->x;
				this->old_y = this->y;
				this->SetPosition(new_x, new_y);
				this->SetState(TELEPORTER_ANI_TELEPORT);
			}
			else if (r == 2) {
				this->new_x = this->x;
				this->new_y = this->y + 50;
				this->old_x = this->x;
				this->old_y = this->y;
				this->SetPosition(new_x, new_y);
				this->SetState(TELEPORTER_ANI_TELEPORT);
			}
			else if (r == 3) {
				this->new_x = this->x;
				this->new_y = this->y - 50;
				this->old_x = this->x;
				this->old_y = this->y;
				this->SetPosition(new_x, new_y);
				this->SetState(TELEPORTER_ANI_TELEPORT);
			}

		}

		timer = 1550;
	}
	else if (timer == 1600) {
		if (this->GetState() == TELEPORTER_ANI_TELEPORT) {

			if (this->new_x - this->old_x > 0 && this->new_y - this->old_y == 0) {
				this->new_x = this->old_x + 50;
				this->new_y = this->old_y;
				this->SetPosition(old_x, old_y);
				this->SetState(TELEPORTER_ANI_TELEPORT1);
			}
			else if (this->new_x - this->old_x < 0 && this->new_y - this->old_y == 0) {
				this->new_x = this->old_x - 50;
				this->new_y = this->old_y;
				this->SetPosition(old_x, old_y);
				this->SetState(TELEPORTER_ANI_TELEPORT1);
			}
			else if (this->new_x - this->old_x == 0 && this->new_y - this->old_y > 0) {
				this->new_x = this->old_x;
				this->new_y = this->old_y - 50;
				this->SetPosition(old_x, old_y);
				this->SetState(TELEPORTER_ANI_TELEPORT1);
			}
			else if (this->new_x - this->old_x == 0 && this->new_y - this->old_y < 0) {
				this->new_x = this->old_x;
				this->new_y = this->old_y + 50;
				this->SetPosition(old_x, old_y);
				this->SetState(TELEPORTER_ANI_TELEPORT1);
			}
		}

		timer = 1600;
	}
	else if (timer == 1650) {

		if (this->GetState() == TELEPORTER_ANI_TELEPORT1) {

			if (this->new_x - this->old_x > 0 && this->new_y - this->old_y == 0) {
				this->SetPosition(old_x + 50, old_y);
				this->SetState(TELEPORTER_ANI_TELEPORT2);
			}
			else if (this->new_x - this->old_x < 0 && this->new_y - this->old_y == 0) {
				this->SetPosition(old_x - 50, old_y);
				this->SetState(TELEPORTER_ANI_TELEPORT2);
			}
			else if (this->new_x - this->old_x == 0 && this->new_y - this->old_y > 0) {
				this->SetPosition(old_x, old_y - 50);
				this->SetState(TELEPORTER_ANI_TELEPORT2);
			}
			else if (this->new_x - this->old_x == 0 && this->new_y - this->old_y < 0) {
				this->SetPosition(old_x, old_y + 50);
				this->SetState(TELEPORTER_ANI_TELEPORT2);
			}
		}

		timer = 1650;
	}
	else if (timer == 1700) {

		if (this->GetState() == TELEPORTER_ANI_TELEPORT2) {

			if (this->new_x - this->old_x > 0 && this->new_y - this->old_y == 0) {
				this->SetPosition(old_x, old_y);
				this->SetState(TELEPORTER_ANI_TELEPORT3);
			}
			else if (this->new_x - this->old_x < 0 && this->new_y - this->old_y == 0) {
				this->SetPosition(old_x, old_y);
				this->SetState(TELEPORTER_ANI_TELEPORT3);
			}
			else if (this->new_x - this->old_x == 0 && this->new_y - this->old_y > 0) {
				this->SetPosition(old_x, old_y);
				this->SetState(TELEPORTER_ANI_TELEPORT3);
			}
			else if (this->new_x - this->old_x == 0 && this->new_y - this->old_y < 0) {
				this->SetPosition(old_x, old_y);
				this->SetState(TELEPORTER_ANI_TELEPORT3);
			}
		}

		timer = 1700;
	}
	else if (timer == 1750) {

		if (this->GetState() == TELEPORTER_ANI_TELEPORT3) {

			jumpStep++;

			if (jumpStep == 1) {

				if (this->new_x - this->old_x > 0 && this->new_y - this->old_y == 0) {
					this->SetPosition(old_x + 50, old_y);
					this->SetState(TELEPORTER_ANI_GRAY_MODE_OFF);
				}
				else if (this->new_x - this->old_x < 0 && this->new_y - this->old_y == 0) {

					this->SetPosition(old_x - 50, old_y);
					this->SetState(TELEPORTER_ANI_GRAY_MODE_OFF);

				}
				else if (this->new_x - this->old_x == 0 && this->new_y - this->old_y > 0) {

					this->SetPosition(old_x, old_y - 50);
					this->SetState(TELEPORTER_ANI_GRAY_MODE_OFF);

				}
				else if (this->new_x - this->old_x == 0 && this->new_y - this->old_y < 0) {

					this->SetPosition(old_x, old_y + 50);
					this->SetState(TELEPORTER_ANI_GRAY_MODE_OFF);
				}

				timer = 1520;

			}
			else {

				if (this->new_x - this->old_x > 0 && this->new_y - this->old_y == 0) {
					this->SetPosition(old_x + 50, old_y);
					this->SetState(TELEPORTER_ANI_GRAY_MODE_ON);
				}
				else if (this->new_x - this->old_x < 0 && this->new_y - this->old_y == 0) {
					this->SetPosition(old_x - 50, old_y);
					this->SetState(TELEPORTER_ANI_GRAY_MODE_ON);
				}
				else if (this->new_x - this->old_x == 0 && this->new_y - this->old_y > 0) {

					this->SetPosition(old_x, old_y - 50);
					this->SetState(TELEPORTER_ANI_GRAY_MODE_ON);

				}
				else if (this->new_x - this->old_x == 0 && this->new_y - this->old_y < 0) {

					this->SetPosition(old_x, old_y + 50);
					this->SetState(TELEPORTER_ANI_GRAY_MODE_ON);
				}

				jumpStep = 0;
				timer = 0;
			}
			
			/*if (teleporter_bullet == NULL)
			{
				teleporter_bullet = new BulletTeleporter(this->x, this->y, this->target);
				teleporter_bullet->SetPosition(this->x + width + 10, this->y + height + 15);
				teleporter_bullet->Set_bullet_dir(this->nx, this->ny);
				teleporter_bullet->Set_IsMove(true);
			}*/
		}
	}
}

bool CTeleporter::CheckCollisionWithRock(vector<LPGAMEOBJECT>* coObjects) {

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	vector<LPGAMEOBJECT> ListRockOVH;
	ListRockOVH.clear();
	
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CRockOVH*>(coObjects->at(i)))
		{
			ListRockOVH.push_back(coObjects->at(i));
		}

	}

	for (int i = 0; i < ListRockOVH.size(); i++)
	{
		if (this->IsCollidingObject(ListRockOVH.at(i)))
		{
			isCollision = true;
		}
	}

	if (!isCollision)
	{
		CalcPotentialCollisions(&ListRockOVH, coEvents);

		if (coEvents.size() == 0)
		{
			isCollision = false;
		}
		else
		{
			isCollision = true;
		}

	}

	if (isCollision)
		return true;
	return false;

}

int CTeleporter::RandomPosition()
{

	int r = rand() % 4;
	
	return r;
}

void CTeleporter::Render()
{
	int ani = TELEPORTER_ANI_GRAY_MODE_ON;

	if (isDoneDeath) return;
	if (hp <= 0) isDeath = true;

	if (isDeath || hp == 0)
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
	if (vy == 1 && vx == -1)
	{
		ani = TELEPORTER_ANI_TELEPORT1;
	}
	if (vy == 1 && vx == 0)
	{
		ani = TELEPORTER_ANI_TELEPORT;
	}
	if (vy == 1 && vx == 1)
	{
		ani = TELEPORTER_ANI_TELEPORT2;
	}
	if (vy == 1 && vx == 2)
	{
		ani = TELEPORTER_ANI_TELEPORT3;
	}

	
	if (teleporter_bullet != NULL)
	{
		teleporter_bullet->Render();
	}

	

	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox(x,y);
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
		vy = 1;
		ny = 0;
		break;
	case TELEPORTER_ANI_TELEPORT1:
		vx = -1;
		nx = 0;
		vy = 1;
		ny = 0;
		break;
	case TELEPORTER_ANI_TELEPORT2:
		vx = 1;
		nx = 0;
		vy = 1;
		ny = 0;
		break;
	case TELEPORTER_ANI_TELEPORT3:
		vx = 2;
		nx = 0;
		vy = 1;
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
