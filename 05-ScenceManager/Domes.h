#pragma once
#include "GameObject.h"
#define DOMES_ANI_WALKING_RIGHT_UP	0
#define DOMES_ANI_WALKING_RIGHT_DOWN	1
#define DOMES_ANI_WALKING_LEFT_UP	2
#define DOMES_ANI_WALKING_LEFT_DOWN	3
#define DOMES_ANI_WALKING_UP_RIGHT	4
#define DOMES_ANI_WALKING_UP_LEFT	5
#define DOMES_ANI_WALKING_DOWN_RIGHT	6
#define DOMES_ANI_WALKING_DOWN_LEFT		7
#define DOMES_STATE_ATACK_NX 8
#define DOMES_STATE_ATACK_NY 9

#define DOMES_WALKING_SPEED 0.03f;
#define	DOMES_JUMPING_SPEED 0.163f;

#define DOMES_BBOX_WIDTH 17
#define DOMES_BBOX_HEIGHT 18
#define DOMES_BBOX_HEIGHT_DIE 16

#define DOMES_STATE_WALKING 100
#define DOMES_STATE_START 200
#define DOMES_STATE_JUMPING 300

class CDomes : public CGameObject
{
	bool isFolow;//theo player
	bool isAtack;
	LPGAMEOBJECT target;
	int numberCollisionBrick = 1;  //số lần chạm tường trước khi tân công
	float boundingHeigt;
	float boundingWight;
	RECT rectBrick = {0,0,5000,5000}; //cục đá va chạm sau cùng, để lấy đố dài của nó 
 //phần gạch đang va chạm


public:
	CDomes(float x, float y,float boundingHeight,float  boundingWight ,LPGAMEOBJECT player);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void Wall();
	void Atack();
	
};

