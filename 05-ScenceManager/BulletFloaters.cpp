#include "BulletFloaters.h"

BulletFloaters::BulletFloaters(float x, float y)
{
	/*vx = 0.5f;
	vy = 0.5f;*/
	this->start_x = start_x;
	this->start_y = start_y;

	isDone = false;
	isMove = true;

	bulletDame = 1;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(16));

	objTag = BULLET_ENEMIES;
	
}

BulletFloaters::~BulletFloaters()
{
}

void BulletFloaters::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	HandleMove(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3);
	if (isDone) return;

	if (isMove)
	{
		if (bullet_dir_x == 1 && bullet_dir_y == 1)
		{
			vx = BULLET_FLOATER_SPEED;
			vy = BULLET_FLOATER_SPEED;
		}
		else if (bullet_dir_x == -1 && bullet_dir_y == 1)
		{
			vx = -BULLET_FLOATER_SPEED;
			vy = BULLET_FLOATER_SPEED;
		}
	}
	else
	{
		return;
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

		// how to push back Sophia if collides with a moving objects, what if Sophia is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!


		//x += min_tx * dx + nx * 0.4f;  //cập nhật lại vị trí x
		//y += min_ty * dy + ny * 0.4f;	// cập nhật lại vị trí y  để tránh bị hụt xuống

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBrick*>(e->obj)) // if e->obj is Goomba 
			{
				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;

				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
				isColBrick = true;
			}
			else if (e->obj->objTag == ENEMY)
			{
				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;
			}
			else if (e->obj->objTag == Player)
			{
				isColPlayer = true;
				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;
			}
		}


	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	


}

void BulletFloaters::Render()
{
	int ani = 0;
	if (isDone) return;
	if (isColBrick)
	{
		ani = BULLET_FLOATER_ANI_COLLISON;
		animation_set->at(ani)->Render(x, y);
		if (animation_set->at(ani)->GetCurrentFrame() == 2)
		{
			isDone = true;
		}
		return;
	}
	else if (isColPlayer) isDone = true;
	else if (isMove)
	{
		if (bullet_dir_x == 1 && bullet_dir_y == 1 )
		{
			ani = BULLET_FLOATER_ANI_WALKING_RIGHT_DOWN;
		}
		else if (bullet_dir == -1 && bullet_dir_y == 1)
		{
			ani = BULLET_FLOATER_ANI_WALKING_LEFT_DOWN;
		}
	}

	RenderBoundingBox();
	aniBullet->Render(x,y);
}

void BulletFloaters::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDone)
	{
		left = x;
		top = y;
		right = x + 10;
		bottom = y + 10;
	}
}
