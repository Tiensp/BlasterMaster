#include "BossHand.h"

CBossHand::CBossHand(float x, float y, int type, float _vx, float _vy)
{
	this->x = x;
	this->y = y;
	this->typeHand = type;
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

void CBossHand::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	Move();
	this->x += dx;
	this->y += dy;


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

