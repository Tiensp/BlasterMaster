#include "BulletObject.h"
#include "Sophia.h"
#include "Brick.h"
#include "Enemy.h"



BulletObject::BulletObject(float _start_x, float _start_y)
{
	/*this->x = 0;
	this->y = 0;*/
	this->start_x = _start_x;
	this->start_y = _start_y;
	isMove = true;
	isDone = false;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(15));
}

BulletObject::~BulletObject()
{
}

void BulletObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	
	HandleMove(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3);
	if (isDone) return;

	if (isMove)
	{
		if (bullet_dir == 1)
		{
			vx = BULLET_SPEDD;
			vy = 0;
		}
		else if (bullet_dir == -1)
		{
			vx = -BULLET_SPEDD;
			vy = 0;
		}
		else
		{
			vx = 0;
			vy = -BULLET_SPEDD;
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
			else if (dynamic_cast<Enemy*>(e->obj))
			{
				/*e->obj->SetState(DOMES_STATE_DIE);*/
				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;

				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
 				isMove = false;
				isColBrick = true;
			}
			
			//else if (dynamic_cast<CGolem*>(e->obj))
			//{
			//	/*e->obj->SetState(DOMES_STATE_DIE);*/
			//	isMove = false;
			//}
		}
	

	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}



void BulletObject::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	right = x + 26;
	top = y;
	bottom = y + 8;
}

void BulletObject::Set_IsMove(const bool& _isMove)
{
	this->isMove = _isMove;
}

void BulletObject::HandleMove(const float x_border, const float y_border)
{
	if (x > start_x + x_border || x < start_x - x_border || y < start_y - y_border)
	{
		isMove = false;
		isDone = true;
	}
	
	

}

void BulletObject::Render()
{
	RenderBoundingBox();
	int ani = 0;
	if (isDone) return;
	if (isColBrick)
	{
		ani = BULLETSOPHIA_STATE_ISCOL_BRICK;
		animation_set->at(ani)->Render(x, y);
		if (animation_set->at(ani)->GetCurrentFrame() == 3)
		{
			isDone = true;
		}
		return;
	
		
	}
	else if (isMove)
	{
		if (bullet_dir == 1)
		{
			ani = 0;
		}
		else if (bullet_dir == -1)
		{
			ani = 1;
		}
		else
		{
			ani = 2;
		}
	}
	
	
	animation_set->at(ani)->Render(x, y);
	/*RenderBoundingBox();*/
}
