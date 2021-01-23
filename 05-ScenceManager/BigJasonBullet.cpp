#include "BigJasonBullet.h"
#include <math.h>
# define M_PI           3.14159265358979323846
#define OHSOPHIABULLET_SPEED 0.25f
#define	OHSOPHIA_RADIUS_SPACE	40.0f
//#define ALPHA	0.00348888888f
#define ALPHA	0.00348888888f
BigJasonBullet::BigJasonBullet()
{
}
BigJasonBullet::BigJasonBullet(float _start_x, float _start_y,  int type,int direct_round)
{

	this->start_x = _start_x;
	this->start_y = _start_y;
	this->type = type;
	isMove = true;
	isDone = false;
	bulletDame = 2;
	radius_increase = 0;
	bullet_direct_round = direct_round;
	
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(19));
}

BigJasonBullet::~BigJasonBullet()
{
}

void BigJasonBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	HandleMove(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	if (isDone) return;
	if (isMove)
	{
		switch (type)
		{
		case 0:
			if (bullet_dir == 1)
			{
				x += 0.125f * dt;
				y = start_y + 10;
			}
			else if (bullet_dir == -1)
			{
				x -= 0.125f * dt;
				y = start_y + 10;
			}
			else if (bullet_dir == 3)
			{
				y -= 0.125f * dt;
			}
			else if (bullet_dir == 4)
			{
				y += 0.125f * dt;
			}
			break;
		case 1:
		{
			radius_increase += 0.5;
			if (bullet_dir == 1) //bắn sang phải
			{
				if (bullet_direct_round == 0)
				{
					x += 0.1f * dt;
				}
				else
				{
					angle += ALPHA * bullet_direct_round * dt;
					if (bullet_direct_round == -1)
					{
						x = point1.x + (OHSOPHIA_RADIUS_SPACE + radius_increase) * cos(angle);
						y = point1.y + (OHSOPHIA_RADIUS_SPACE + radius_increase) * sin(angle);
					}
					else
					{
						x = point1.x + (OHSOPHIA_RADIUS_SPACE + radius_increase) * cos(angle);
						y = point1.y + (OHSOPHIA_RADIUS_SPACE + radius_increase) * sin(angle);
					}

				}
			}
			else if (bullet_dir == -1)
			{
				if (bullet_direct_round == 0)
				{
					x -= 0.1f * dt;
				}
				else
				{
					angle += ALPHA * bullet_direct_round * dt;
					if (bullet_direct_round == -1)
					{
						x = point1.x + (OHSOPHIA_RADIUS_SPACE + radius_increase) * cos(angle);
						y = point1.y + (OHSOPHIA_RADIUS_SPACE + radius_increase) * sin(angle);
					}
					else
					{
						x = point1.x + (OHSOPHIA_RADIUS_SPACE + radius_increase) * cos(angle);
						y = point1.y + (OHSOPHIA_RADIUS_SPACE + radius_increase) * sin(angle);
					}
				}
			}
			else if (bullet_dir == 3)
			{
				if (bullet_direct_round == 0)
				{
					y -= 0.1f * dt;
				}
				else
				{
					angle += ALPHA * bullet_direct_round * dt;
					if (bullet_direct_round == -1)
					{
						x = point1.x + (OHSOPHIA_RADIUS_SPACE + radius_increase) * cos(angle);
						y = point1.y + (OHSOPHIA_RADIUS_SPACE + radius_increase) * sin(angle);
					}
					else
					{
						x = point1.x + (OHSOPHIA_RADIUS_SPACE + radius_increase) * cos(angle);
						y = point1.y + (OHSOPHIA_RADIUS_SPACE + radius_increase) * sin(angle);
					}
				}
			}
			else if (bullet_dir == 4)
			{
				if (bullet_direct_round == 0)
				{
					y += 0.1f * dt;
				}
				else
				{
					angle += ALPHA * bullet_direct_round * dt;
					if (bullet_direct_round == -1)
					{
						x = point1.x + (OHSOPHIA_RADIUS_SPACE + radius_increase) * cos(angle);
						y = point1.y + (OHSOPHIA_RADIUS_SPACE + radius_increase) * sin(angle);
					}
					else
					{
						x = point1.x + (OHSOPHIA_RADIUS_SPACE + radius_increase) * cos(angle);
						y = point1.y + (OHSOPHIA_RADIUS_SPACE + radius_increase) * sin(angle);
					}
				}
			}
			break;
		}
		case 2:
		{
			angle += ALPHA * bullet_direct_round * dt * 5;
			if (bullet_dir == 1)
			{
				x += 0.125f * dt;
				y = (start_y + 20) + OHSOPHIA_RADIUS_SPACE * sin(angle);
			}
			else if (bullet_dir == -1)
			{
				x -= 0.125f * dt;
				y = (start_y + 20) + OHSOPHIA_RADIUS_SPACE * sin(angle);
			}
			else if (bullet_dir == 3)
			{
				y -= 0.125f * dt;
				x = (start_x + 30) + OHSOPHIA_RADIUS_SPACE * cos(angle);
			}
			else if (bullet_dir == 4)
			{
				y += 0.125f * dt;
				x = (start_x + 30) + OHSOPHIA_RADIUS_SPACE * cos(angle);
			}
			break;
		}

		}
	}
	CheckCollisionWithCBrick(coObjects);
	CheckCollisionWithEnemy(coObjects);


}

void BigJasonBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	if (!isDone)
	{
		left = x;
		right = x + 10;
		top = y;
		bottom = y + 10;
	}
}

void BigJasonBullet::Render()
{
	int ani = 0;
	if (isDone) return;
	else if (isColBrick)
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
		if (bullet_dir == 1)
		{
			ani = 2;
		}
		else if (bullet_dir == -1)
		{
			ani = 0;
		}
		else if (bullet_dir == 3)
		{
			ani = 1;
		}
		else if (bullet_dir == 4)
		{
			ani = 3;
		}
	}
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox(x, y);
}

void BigJasonBullet::Set_Bullet_list()
{

}

void BigJasonBullet::Set_point()
{
	float pi = 2 * acos(0.0);
	if (type == 1)
	{
		if (bullet_dir == 1)
		{
			if (bullet_direct_round == 1)
			{
				this->angle = -pi / 2;
				this->point1.x = start_x + OHSOPHIA_RADIUS_SPACE + 10;
				this->point1.y = start_y + OHSOPHIA_RADIUS_SPACE + 10;
			}
			else if (bullet_direct_round == -1)
			{
				this->angle = pi / 2;
				this->point1.x = start_x + OHSOPHIA_RADIUS_SPACE + 10;
				this->point1.y = start_y - OHSOPHIA_RADIUS_SPACE;
			}

		}
		else if (bullet_dir == -1)
		{
			if (bullet_direct_round == 1)
			{
				this->angle = pi / 2;
				this->point1.x = start_x - 10;
				this->point1.y = start_y - 5;
			}
			else
			{
				this->angle = -pi / 2;
				this->point1.x = start_x - 10;
				this->point1.y = start_y + OHSOPHIA_RADIUS_SPACE + 10;
			}
		}
		else if (bullet_dir == 3)
		{
			if (bullet_direct_round == 1)
			{
				this->angle = -pi / 2;
				this->point1.x = start_x + OHSOPHIA_RADIUS_SPACE - 10;
				this->point1.y = start_y + 5;
			}
			else
			{
				this->angle = -pi / 2;
				this->point1.x = start_x;
				this->point1.y = start_y + 5;
			}
		}
		else if (bullet_dir == 4)
		{
			if (bullet_direct_round == 1)
			{
				this->angle = pi / 2;
				this->point1.x = start_x + OHSOPHIA_RADIUS_SPACE - 10;
				this->point1.y = start_y + 12;
			}
			else
			{
				this->angle = pi / 2;
				this->point1.x = start_x + 5;
				this->point1.y = start_y + 10;
			}
		}
	}
	else if (type == 2)
	{
		if (bullet_dir == 1)
		{
			angle = -pi;
		}
		else if (bullet_dir == -1)
		{
			angle = pi;
		}
		else if (bullet_dir == 3)
		{
			angle = pi;
		}
		else if (bullet_dir == 4)
		{
			angle = -pi;
		}
	}


}

void BigJasonBullet::CheckCollisionWithEnemy(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	bool isColideUsingAABB = false;
	coEvents.clear();
	vector<LPGAMEOBJECT> ListEnemy;
	ListEnemy.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (dynamic_cast<Enemy*>(coObjects->at(i)))
		{
			ListEnemy.push_back(coObjects->at(i));
		}
	for (UINT i = 0; i < ListEnemy.size() && isColideUsingAABB == false; i++)
	{
		if (this->IsCollidingObject(ListEnemy.at(i)))
		{
			isColideUsingAABB = true;
			Enemy* enemy = dynamic_cast<Enemy*>(ListEnemy.at(i));
			enemy->Set_hp(bulletDame);
			/*this->isMove = false;*/
			this->isColEnemy = true;
			this->isDone = true;
		}
	}
	if (isColideUsingAABB != true)
	{
		CalcPotentialCollisions(&ListEnemy, coEvents);
		if (coEvents.size() == 0)
		{

		}
		else
		{

			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;

			// TODO: This is a very ugly designed function!!!!
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
			LPCOLLISIONEVENT e = coEventsResult[0];
			Enemy* enemy = dynamic_cast<Enemy*>(e->obj);
			enemy->Set_hp(bulletDame);
			this->isDone = true;

			/*Item->IsDead = true;*/

		}
	}

}

void BigJasonBullet::CheckCollisionWithCBrick(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	bool isColideUsingAABB = false;
	coEvents.clear();
	vector<LPGAMEOBJECT> ListBrick;
	ListBrick.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (dynamic_cast<CBrick*>(coObjects->at(i)))
		{
			ListBrick.push_back(coObjects->at(i));
		}
	for (UINT i = 0; i < ListBrick.size() && isColideUsingAABB == false; i++)
	{
		if (this->IsCollidingObject(ListBrick.at(i)))
		{
			isColideUsingAABB = true;
			this->isColBrick = true;
			
		}
	}
	if (isColideUsingAABB != true)
	{
		CalcPotentialCollisions(&ListBrick, coEvents);
		if (coEvents.size() == 0)
		{

		}
		else
		{

			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;

			// TODO: This is a very ugly designed function!!!!
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
			this->isColBrick = true;

		}
	}
}
