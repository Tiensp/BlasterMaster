#include "BossHand.h"
#include "BigJason.h"
#include "Sound.h"

CBossHand::CBossHand(float x, float y, int type, float _vx, float _vy)
{
	this->x = x;
	this->y = y;
	this->typeHand = type;
	hp = 999;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(120));
	if (typeHand == 1) {

		SetSpeed(-BOSS_HAND_WALKING_SPEED_X, -BOSS_HAND_WALKING_SPEED_Y);
	}
	else
	{

		SetSpeed(BOSS_HAND_WALKING_SPEED_X, BOSS_HAND_WALKING_SPEED_Y);
	}



	//this->SetSpeed(_vx, _vy);
	/*new_vx = _vx;
	new_vy = _vy;*/
}

CBossHand::~CBossHand()
{
}

void CBossHand::CheckCollisionWithBigJson(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	bool isColideUsingAABB = false;
	coEvents.clear();
	vector<LPGAMEOBJECT> ListEnemy;
	ListEnemy.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (dynamic_cast<CBigJason*>(coObjects->at(i)))
		{
			ListEnemy.push_back(coObjects->at(i));
		}
	for (UINT i = 0; i < ListEnemy.size(); i++)
	{
		if (this->IsCollidingObject(ListEnemy.at(i)))
		{
			isColideUsingAABB = true;
		
			if (dynamic_cast<CBigJason*>(coObjects->at(i)))
			{
				CBigJason* bigJason = dynamic_cast<CBigJason*>(ListEnemy.at(i));
				isColideUsingAABB = true;
				if (bigJason->GetUntouchable() == 1 || bigJason->GetIsInjured()==true)
					continue;
				bigJason->SetHealthWithBullet(1);
				Sound::GetInstance()->Play("PlayerInjured", 0, 1);
				
				bigJason->StartUntouchable();
			}

		}

	}
	if (isColideUsingAABB != true)
	{
		CalcPotentialCollisions(&ListEnemy, coEvents);
		if (coEvents.size() == 0)
		{
			/*x += dx;
			y += dy;*/
		}
		else
		{

			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;

			// TODO: This is a very ugly designed function!!!!
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
			LPCOLLISIONEVENT e = coEventsResult[0];
			if (dynamic_cast<CBigJason*>(e->obj))
			{
				CBigJason* bigJason = dynamic_cast<CBigJason*>(e->obj);
				

				bigJason->SetHealthWithBullet(1);
				Sound::GetInstance()->Play("PlayerInjured", 0, 1);
			}
			


		}
	}

}

void CBossHand::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::Update(dt, coObjects);
	Move();
	this->x += dx;
	this->y += dy;
	CheckCollisionWithBigJson(coObjects);


}
void CBossHand::Render()
{
	int ani;
	if (typeHand == 1)
	{
		ani = 0;
	}
	else
	{
		ani = 1;
	}
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox(x, y);


}
void CBossHand::Move() {
	float left_hand_min_x = x_boss - 60;
	float left_hand_max_x = x_boss + 40;
	float left_hand_min_y = y_boss - 90;
	float left_hand_max_y = y_boss + 90;
	float hand_max_y = y_boss + 90;
	float hand_min_y = y_boss - 40;
	float right_hand_max_x = x_boss + 102;
	float right_hand_min_x = x_boss + 20;
	float right_hand_min_y = y_boss - 90;
	float right_hand_max_y = y_boss + 90;

	if (typeHand == 1) {
		if (x >= left_hand_max_x)
			vx = -BOSS_HAND_WALKING_SPEED_X;
		else if (x <= left_hand_min_x) {
			vx = BOSS_HAND_WALKING_SPEED_X;
		}
		if (y <= left_hand_min_y)
		{
			vy = BOSS_HAND_WALKING_SPEED_Y;
			//isStop = false;
		}
		else if (y >= left_hand_max_y)
		{
			vy = -BOSS_HAND_WALKING_SPEED_Y;
			//isStop = false;
		}
	}
	else {
		if (x >= right_hand_max_x)
			vx = -BOSS_HAND_WALKING_SPEED_X;
		else if (x <= right_hand_min_x) {
			vx = BOSS_HAND_WALKING_SPEED_X;
		}
		if (y <= right_hand_min_y)
		{
			vy = BOSS_HAND_WALKING_SPEED_Y;
			//isStop = false;
		}
		else if (y >= right_hand_max_y)
		{
			vy = -BOSS_HAND_WALKING_SPEED_Y;
			//isStop = false;
		}
	}

	DebugOut(L"vy %f\n", vy);
}
void CBossHand::SetBossPos(float x_boss, float y_boss)
{
	this->x_boss = x_boss;
	this->y_boss = y_boss;
}

