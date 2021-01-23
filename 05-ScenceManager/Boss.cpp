#include "Boss.h"
#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Sophia.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"
#include "Brick.h"
#include "BossArm.h"
#include "PlayScence.h"
#define BIT					16

CBoss* CBoss::_instance = NULL;


CBoss* CBoss::GetInstance()
{
	if (_instance == NULL) {
		_instance = new CBoss();
	}
	return _instance;
}
CBoss::CBoss()
{
}
CBoss::CBoss(float x, float y, LPGAMEOBJECT player)
{
	hp = 5;
	SetState(BOSS_ANI_WALKING_RIGHT_DOWN);


	this->x = x;
	this->y = y;
	this->target = player;
	CBossHand* hand1 = new CBossHand(this->x - 20, this->y + 10, 1, this->x, this->x);
	listBossHand.push_back(hand1);
	//DebugOut(L"succesful2");
	CBossHand* hand2 = new CBossHand(this->x + 62, this->y + 10, 2, this->x, this->x);
	listBossHand.push_back(hand2);
	for (int i = 0; i < 4; i++)
	{
		CBossArm* arm = new CBossArm(this->x - 20, this->y + 10, 1, 0.027 + 0.0035 * (i + 1), 0.027 + 0.0035 * (i + 1));
		listBossArm.push_back(arm);
	}
	for (int i = 0; i < 4; i++)
	{
		CBossArm* arm = new CBossArm(this->x +62 , this->y + 10, 2, 0.027 + 0.0035 * (i + 1), 0.027 + 0.0035 * (i + 1));
		listBossArm.push_back(arm);
	}
	objTag = BOSS_TAG;
	objType = BOSS;
}

void CBoss::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDeath)
	{
		left = x;
		top = y;
		right = x + BOSS_BBOX_WIDTH;
		bottom = y + BOSS_BBOX_HEIGHT;
	}


	/*if (state == FLOATER_STATE_DIE)
		bottom = y + FLOATER_BBOX_HEIGHT_DIE;
	else
		bottom = y + FLOATER_BBOX_HEIGHT;*/
}

void CBoss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isDeath)
	{
		Enemy::Update(dt, coObjects);

		//for (int i = 0; i < listBulletBoss.size(); i++)
		//{
		//	listBulletBoss[i]->Update(dt, coObjects);
		//}
		timeToAttack += 20;

		if (timeToAttack == 1300) {

			if (this->x - target->x > 0) {
				this->nx = -1;
			}
			else if (this->x - target->x < 0) {
				this->nx = 1;
			}
			isAttack = true;
			timeToAttack = 0;
		}
		else
		{
			isAttack = false;

		}
		/*listBossHand[0]->SetSpeed(BOSS_HAND_WALKING_SPEED_X, BOSS_HAND_WALKING_SPEED_Y);
		listBossHand[1]->SetSpeed(-BOSS_HAND_WALKING_SPEED_X, -BOSS_HAND_WALKING_SPEED_Y);*/
		for (int i = 0; i < listBossHand.size(); i++) {
			listBossHand[i]->SetBossPos(this->x, this->y);
			listBossHand[i]->Update(dt, coObjects);
		}

		float x_hand_left, y_hand_left, x_hand_right, y_hand_right;
		float x_diff_left, y_diff_left;
		float x_diff_right, y_diff_right;

		listBossHand[0]->GetPosition(x_hand_left, y_hand_left);


		listBossHand[1]->GetPosition(x_hand_right, y_hand_right);

		//listBossArm[0]->SetX(x + 6);
		//listBossArm[3]->SetXYFollow(x_hand_left, y_hand_left);


		x_diff_left = x_hand_left - x;
		y_diff_left = y_hand_left - y;
		listBossArm[0]->SetXYFollow(x - 5 + x_diff_left * 1 / 5, y + 6 + y_diff_left * 1 / 5);
		listBossArm[1]->SetXYFollow(x - 5 + x_diff_left * 2 / 5, y + 6 + y_diff_left * 2 / 5);
		listBossArm[2]->SetXYFollow(x - 5 + x_diff_left * 3 / 5, y + 6 + y_diff_left * 3 / 5);
		listBossArm[3]->SetXYFollow(x - 5 + x_diff_left * 4 / 5, y + 6 + y_diff_left * 4 / 5);

		x_diff_right = x_hand_right - (x + 50);
		y_diff_right = y_hand_right - y;

		listBossArm[4]->SetXYFollow(x + 50 + x_diff_right * 1 / 5, y + 6 + y_diff_right * 1 / 5);
		listBossArm[5]->SetXYFollow(x + 50 + x_diff_right * 2 / 5, y + 6 + y_diff_right * 2 / 5);
		listBossArm[6]->SetXYFollow(x + 50	+ x_diff_right * 3 / 5, y + 6 + y_diff_right * 3 / 5);
		listBossArm[7]->SetXYFollow(x + 50 + x_diff_right * 4 / 5, y + 6 + y_diff_right * 4 / 5);

		for (int i = 0; i < listBossArm.size(); i++)
		{
			listBossArm[i]->Update(dt, coObjects);
		}



		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		CalcPotentialCollisions(coObjects, coEvents);

		if (coEvents.size() == 0)  //nếu không có va chạm, update bình thường
		{
		/*		x += dx;
				y += dy;*/
		}
		else //có va chạm
		{
			float min_tx, min_ty, nx = 0, ny = 0;
			float rdx = 0;
			float rdy = 0;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);  // sắp xếp lại các sự kiện va chạm đầu tiên theo trục x, y 

			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<CBrick*>(e->obj)) // if e->obj is Goomba 
				{
					x += min_tx * dx + nx * 0.4f;  //cập nhật lại vị trí x
					y += min_ty * dy + ny * 0.4f;
					if (nx != 0) vx = 0;
					if (ny != 0) vy = 0;// cập nhật lại vị trí y  để tránh bị hụt xuống

					CBrick* brick = dynamic_cast<CBrick*>(e->obj);

					// jump on top >> kill Goomba and deflect a bit 
					if (e->nx != 0)
					{
						if (e->nx > 0)
						{
							if (this->ny > 0)
							{
								this->SetState(BOSS_ANI_WALKING_RIGHT_DOWN);
							}
							else if (this->ny < 0)
							{
								this->SetState(BOSS_ANI_WALKING_RIGHT_UP);
							}
						}
						else
						{
							if (this->ny > 0)
							{
								this->SetState(BOSS_ANI_WALKING_LEFT_DOWN);
							}
							else  if (this->ny < 0)
							{
								this->SetState(BOSS_ANI_WALKING_LEFT_UP);
							}
						}

					}
					else if (e->ny != 0)
					{
						if (e->ny > 0)
						{
							if (this->nx > 0)
							{
								this->SetState(BOSS_ANI_WALKING_RIGHT_DOWN);
							}
							else if (this->nx < 0)
							{
								this->SetState(BOSS_ANI_WALKING_LEFT_DOWN);
							}
						}
						else if (e->ny < 0)
						{
							if (this->nx > 0)
							{
								this->SetState(BOSS_ANI_WALKING_RIGHT_UP);
							}
							else if (this->nx < 0)
							{
								this->SetState(BOSS_ANI_WALKING_LEFT_UP);
							}
						}
					}
				}
				/*if (e->obj->objTag == PLAYER)
				{
					x += dx;
					y += dy;
				}
				if (e->obj->objTag == ENEMY)
				{
					x += dx;
					y += dy;
				}*/
			}
		}
	}

}


void CBoss::Attack()
{
	if (abs(this->x - target->x) <= 200)
	{
		isAttack = true;
		if (this->nx - target->nx == 0 && nx > 0)
		{
			/*if (boss_bullet == NULL && this->nx)
			{
				boss_bullet = new BossBullet(this->x, this->y);
				boss_bullet->SetPosition(this->x, this->y);
				boss_bullet->Set_bullet_dir(this->nx);
				boss_bullet->Set_IsMove(true);
			}*/
		}
		else if (this->nx - target->nx == 0 && nx < 0)
		{
			/*if (boss_bullet == NULL && this->nx)
			{
				boss_bullet = new BossBullet(this->x, this->y);
				boss_bullet->SetPosition(this->x, this->y);
				boss_bullet->Set_bullet_dir(this->nx);
				boss_bullet->Set_IsMove(true);
			}*/
		}
	}
	else
	{
		isAttack = false;
	}
}


void CBoss::Render()
{
	int ani = BOSS_ANI_WALKING_RIGHT_DOWN;
	if (isDeath)
	{
		return;
	}
	else
	{
		if (nx > 0)
		{
			if (ny > 0)
			{
				ani = BOSS_ANI_WALKING_RIGHT_DOWN;
			}
			else if (ny < 0)
			{
				ani = BOSS_ANI_WALKING_RIGHT_UP;
			}
		}
		else if (nx < 0)
		{
			if (ny > 0)
			{
				ani = BOSS_ANI_WALKING_LEFT_DOWN;
			}
			else if (ny < 0)
			{
				ani = BOSS_ANI_WALKING_LEFT_UP;
			}
		}
	}
	for (int i = 0; i < listBossHand.size(); i++) {

		listBossHand[i]->Render();
	}
	for (int i = 0; i < listBossArm.size(); i++)
	{
		listBossArm[i]->Render();
	}


	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox(x, y);
}

int CBoss::Get_Boss_bullet()
{
	return 0;
}

void CBoss::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		/*case FLOATER_STATE_DIE:
			y += FLOATER_BBOX_HEIGHT - FLOATER_BBOX_HEIGHT_DIE + 1;
			vx = 0;
			vy = 0;
			break;*/
	case BOSS_ANI_WALKING_LEFT_UP:
		vx = -BOSS_WALKING_SPEED;
		nx = -1;
		vy = -BOSS_JUMPING_SPEED;
		ny = -1;
		break;
	case BOSS_ANI_WALKING_LEFT_DOWN:
		vx = -BOSS_WALKING_SPEED;
		nx = -1;
		vy = BOSS_JUMPING_SPEED;
		ny = 1;
		break;
	case BOSS_ANI_WALKING_RIGHT_UP:
		vx = BOSS_WALKING_SPEED;
		nx = 1;
		vy = -BOSS_JUMPING_SPEED;
		ny = -1;
		break;
	case BOSS_ANI_WALKING_RIGHT_DOWN:
		vx = BOSS_WALKING_SPEED;
		nx = 1;
		vy = BOSS_JUMPING_SPEED;
		ny = 1;
		break;
	}
}
