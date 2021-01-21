#pragma once
#include "GameObject.h"
#include "Enemy.h"
#define TELEPORTER_ANI_GRAY_MODE_ON 0
#define TELEPORTER_ANI_GRAY_MODE_OFF 1
#define TELEPORTER_ANI_TELEPORT 2
#define TELEPORTER_ANI_DEATH 3


#define TELEPORTER_BBOX_WIDTH 25
#define TELEPORTER_BBOX_HEIGHT 33
#define TELEPORTER_BBOX_HEIGHT_DIE 32

class CTeleporter : public Enemy
{
	LPGAMEOBJECT target;

	int interval = 10;
	int timer;
	int jumpStep = 4;
	int new_x, new_y;

	bool isDeath;
	bool isDoneDeath;
public:
	CTeleporter(float x, float y, LPGAMEOBJECT player, int _typeItem);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	
	int  RandomPosition(int a, int b);

	void ChangeState();
	void flowPlayer(LPGAMEOBJECT player);
};




