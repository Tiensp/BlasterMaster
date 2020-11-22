#include "Domes.h"
#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Sophia.h"
#include "Game.h"
#include "Camera.h"
#include "Goomba.h"
#include "Portal.h"
#include "Brick.h"
CDomes::CDomes(float x, float y, LPGAMEOBJECT player)
{
	SetState(DOMES_STATE_START);
	this->x = x;
	this->y = y;
	this->target = player;
	

}

void CDomes::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + DOMES_BBOX_WIDTH;

	if (state == DOMES_STATE_START)
		bottom = y + DOMES_BBOX_HEIGHT_DIE;
	else
		bottom = y + DOMES_BBOX_HEIGHT;
}

void CDomes::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//vx -= 0.0005f * dt;

	//DebugOut(L"golumnvX: %f, golumnvY: %f\n", vx, vy);
	CGameObject::Update(dt, coObjects);
	//DebugOut(L"golumnvX: %f, golumnvY: %f\n", vx, vy);



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
		if (this->GetState() == DOMES_ANI_WALKING_DOWN_LEFT)
		{
			
		}
		
			x += dx;
			y += dy;
		
	
		
			
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
				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;

				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
				
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);
			

				if (e->ny != 0 )
				{
				
					if (e->ny < 0)
					{
						if (this->nx > 0 )
						{
							if (this->GetState() == DOMES_ANI_WALKING_DOWN_LEFT)
							{
								this->SetState(DOMES_ANI_WALKING_LEFT_UP);
							}
							else
							{
								this->SetState(DOMES_ANI_WALKING_RIGHT_UP);
							}
							
						}
						else if(this-> nx < 0)
						{
							if (this->GetState() == DOMES_ANI_WALKING_DOWN_RIGHT)
							{
								this->SetState(DOMES_ANI_WALKING_RIGHT_UP);
							}
							else
							{
								this->SetState(DOMES_ANI_WALKING_LEFT_UP);
							}
							
						}
					}
					else 
					{
						if (this->nx > 0 )
						{
							
							this->SetState(DOMES_ANI_WALKING_RIGHT_DOWN);
						}
						else 
						{
							if (this->GetState() == DOMES_ANI_WALKING_UP_RIGHT)
							{
								this->SetState(DOMES_ANI_WALKING_RIGHT_DOWN);
							}
							else
							{
								this->SetState(DOMES_ANI_WALKING_LEFT_DOWN);
							}
							
						}
					}
				
				}
				else if (e->nx != 0 )
				{
					if (e->nx > 0)
					{
						if (this->ny < 0 )
						{
						
							this->SetState(DOMES_ANI_WALKING_UP_RIGHT);
						}
						else 
						{
							this->SetState(DOMES_ANI_WALKING_DOWN_RIGHT);
						}
					}
					else 
					{
						if (this->ny < 0 )
						{
							if (this->GetState() == DOMES_ANI_WALKING_RIGHT_DOWN)
							{
								this->SetState(DOMES_ANI_WALKING_DOWN_LEFT);
							}
							else
							{
								this->SetState(DOMES_ANI_WALKING_UP_LEFT);
							}
							
						}
						else 
						{
							this->SetState(DOMES_ANI_WALKING_DOWN_LEFT);
						}
					}
				
				}
				
			
				// jump on top >> kill Goomba and deflect a bit 
			
			
			}
			
		}



	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}



void CDomes::Render()
{
	int ani;
	if (this->GetState() == DOMES_STATE_START)
	{
		ani = 0; 
	}
	if (vx > 0 && vy == 0)
	{
		if (nx > 0 && ny > 0) ani = DOMES_ANI_WALKING_RIGHT_UP;
		else if (nx > 0 && ny < 0) ani = DOMES_ANI_WALKING_RIGHT_DOWN;
	}
	else if (vx < 0 && vy == 0)
	{
		if (nx < 0 && ny > 0) ani = DOMES_ANI_WALKING_LEFT_UP;
		else if (nx < 0 && ny < 0) ani = DOMES_ANI_WALKING_LEFT_DOWN;
	}
	else if (vy > 0 && vx == 0)
	{
		if (ny > 0 && nx > 0) ani = DOMES_ANI_WALKING_DOWN_LEFT;
		else if (ny > 0 && nx < 0) ani = DOMES_ANI_WALKING_DOWN_RIGHT;
	}
	else if (vy < 0 && vx == 0)
	{
		if (ny < 0 && nx > 0) ani = DOMES_ANI_WALKING_UP_LEFT;
		else if (ny < 0 && nx < 0) ani = DOMES_ANI_WALKING_UP_RIGHT;
	}

		
	
	DebugOut(L"ani %d\n", ani);
	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}

void CDomes::Convert(int nx, int ny)
{
	int nx1 = nx;
	int ny1 = ny;
	this->nx = ny1;
	this->ny = nx1;

}



void CDomes::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case DOMES_STATE_START:
		vx= -DOMES_WALKING_SPEED;
		vy = 0;
		ny = -1;
		nx =1;
		break;
	case DOMES_ANI_WALKING_RIGHT_UP:
		vx = DOMES_WALKING_SPEED;
		vy = 0;
		nx = 1;
		ny = 1;
		break;
	case DOMES_ANI_WALKING_LEFT_UP:
		vx = -DOMES_WALKING_SPEED;
		vy = 0;
		nx = -1;
		ny = 1;
		break;
	case DOMES_ANI_WALKING_RIGHT_DOWN:
		vx = DOMES_WALKING_SPEED;
		vy = 0;
		nx = 1;
		ny = -1;
		break;
	case DOMES_ANI_WALKING_LEFT_DOWN:
		vx = -DOMES_WALKING_SPEED;
		vy = 0;
		nx = -1;
		ny = -1;
		break;
	case DOMES_ANI_WALKING_UP_RIGHT:
		vy = -DOMES_WALKING_SPEED;
		vx = 0;
		ny = -1;
		nx = -1;
		break;
	case DOMES_ANI_WALKING_DOWN_RIGHT:
		vx = 0;
		vy = DOMES_WALKING_SPEED;
		ny = 1;
		nx = -1;
		break;
	case DOMES_ANI_WALKING_UP_LEFT:
		vx = 0;
		vy = -DOMES_WALKING_SPEED;
		ny = -1;
		nx = 1;
		break;
	case DOMES_ANI_WALKING_DOWN_LEFT:
		vx = 0;
		vy = DOMES_WALKING_SPEED;
		ny = 1;
		nx = 1;
		break;
	}
}
