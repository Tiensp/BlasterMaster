#pragma once
#include "GameObject.h"
#define DOMES_ANI_WALKING_RIGHT_UP	0
#define DOMES_ANI_WALKING_RIGHT_DOWN	1
#define DOMES_ANI_WALKING_LEFT_UP	3
#define DOMES_ANI_WALKING_LEFT_DOWN	4
#define DOMES_ANI_WALKING_UP_RIGHT	5
#define DOMES_ANI_WALKING_UP_LEFT	6
#define DOMES_ANI_WALKING_DOWN_RIGHT	7
#define DOMES_ANI_WALKING_DOWN_LEFT		8

#define DOMES_WALKING_SPEED 0.03f;
#define	DOMES_JUMPING_SPEED 0.163f;

#define DOMES_BBOX_WIDTH 17
#define DOMES_BBOX_HEIGHT 18
#define DOMES_BBOX_HEIGHT_DIE 16

#define DOMES_STATE_WALKING 100
#define DOMES_STATE_DIE 200
#define DOMES_STATE_JUMPING 300

class CDomes : public CGameObject
{
	bool isFolow;  //theo player 
	LPGAMEOBJECT target;




public:
	CDomes(float x, float y, LPGAMEOBJECT player);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void flowPlayer(LPGAMEOBJECT player);
};

