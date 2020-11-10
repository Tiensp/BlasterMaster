#include "Golem.h"
CGolem::CGolem()
{
	SetState(GOLEM_STATE_WALKING);

}

void CGolem::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + GOLEM_BBOX_WIDTH;

	if (state == GOLEM_STATE_DIE)
		bottom = y + GOLEM_BBOX_HEIGHT_DIE;
	else
		bottom = y + GOLEM_BBOX_HEIGHT;
}

void CGolem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	x += dx;
	y += dy;

	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
	}

	if (vx > 0 && x > 290) {
		x = 290; vx = -vx;
	}

}

void CGolem::Render()
{
	int ani = GOLEM_ANI_WALKING_RIGHT;
	if (vx > 0) ani = GOLEM_ANI_WALKING_RIGHT;
	else if (vx <= 0) ani = GOLEM_ANI_WALKING_LEFT;

	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}



void CGolem::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOLEM_STATE_DIE:
		y += GOLEM_BBOX_HEIGHT - GOLEM_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case GOLEM_STATE_WALKING:
		vx = GOLEM_WALKING_SPEED;
		break;
	}
}
