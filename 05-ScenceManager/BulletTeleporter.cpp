#include "BulletTeleporter.h"
BulletTeleporter::BulletTeleporter(float _start_x, float _start_y, LPGAMEOBJECT player)
{
	this->start_x = _start_x;
	this->start_y = _start_y;
	this->target = player;
	isMove = true;
	isDone = false;
	bulletDame = 1;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(24));
}

BulletTeleporter::~BulletTeleporter()
{
}

void BulletTeleporter::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CEnemyBullet::Update(dt, coObjects);
	if (isDone) return;

	if (isMove)
	{
		if (bullet_dir_x == 1 && bullet_dir_y == 1)
		{
			vx = 0.155f;
			vy = 0.130f;
		}
		else if (bullet_dir == -1 && bullet_dir_y == 1)
		{
			vx = -0.155f;
			vy = 0.130f;
		}
		else if (bullet_dir_x == 1 && bullet_dir_y == -1)
		{
			vx = 0.155f;
			vy = -0.130f;
		}
		else if (bullet_dir_x == -1 && bullet_dir_y == -1)
		{
			vx = -0.155f;
			vy = -0.130f;
		}
	}
	else
	{
		return;
	}


	if (followPlayer == 1)
	{
		if (nx > 0 && ny > 0)
		{
			this->SetState(1);
			followPlayer++;
		}
		else if (nx > 0 && ny < 0)
		{
			this->SetState(0);
			followPlayer++;
		}
		else if (nx < 0 && ny > 0)
		{
			this->SetState(2);
			followPlayer++;
		}
		else if (nx < 0 && ny < 0)
		{
			this->SetState(3);
			followPlayer++;
		}
	}

	if (this->x - target->x <= 0)
	{
		nx = 1;
	}
	else if (this->x - target->x > 0)
	{
		nx = -1;
	}

	if (this->y - target->y <= 0)
	{
		ny = 1;
	}
	else if (this->x - target->x > 0)
	{
		ny = -1;
	}


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
	}
	else //có va chạm
	{
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);  // sắp xếp lại các sự kiện va chạm đầu tiên theo trục x, y 



		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBrick*>(e->obj)) // if e->obj is Goomba 
			{
				/*x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;*/

				/*if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;*/

				//isDone = true; 
				isColBrick = true;
			}
			else if (e->obj->objTag == ENEMY)
			{
				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;
			}
			else if (e->obj->objTag == PLAYER)
			{
				isColPlayer = true;
				/*x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;*/
			}
		}


	}
	//for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void BulletTeleporter::Render()
{
	int ani = 0;
	if (isDone) return;
	if (isColBrick)
	{
		isDone = true;
	}
	else if (isColPlayer)
	{
		ani = 4;
		animation_set->at(ani)->Render(x, y);
		if (animation_set->at(ani)->GetCurrentFrame() == 0)
		{
			isDone = true;
		}
		return;
	}
	else if (isMove)
	{
		if (bullet_dir_x == 1 && bullet_dir_y == -1)
		{
			ani = 0;
		}
		else if (bullet_dir == 1 && bullet_dir_y == 1)
		{
			ani = 1;
		}
		else if (bullet_dir_x == -1 && bullet_dir_y == 1)
		{
			ani = 2;
		}
		else if (bullet_dir_x == -1 && bullet_dir_y == -1)
		{
			ani = 3;
		}
	}

	if (!isDone)
	{
		nx = nx;
		ny = ny;
	}
	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void BulletTeleporter::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDone)
	{
		left = x;
		top = y;
		right = x + 10;
		bottom = y + 10;
	}
}

void BulletTeleporter::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case 0:
		vx = 0.155f;
		vy = -0.105f;
		nx = 1;
		ny = -1;
		break;
	case 1:
		vx = 0.155f;
		vy = 0.130f;
		nx = 1;
		ny = 1;
		break;
	case 2:
		vx = -0.155f;
		vy = 0.130f;
		nx = -1;
		ny = 1;
		break;
	case 3:
		vx = -0.155f;
		vy = -0.130f;
		nx = -1;
		ny = -1;
		break;
	case 4:
		vx = vy = nx = ny = 0;
		break;
	}
}