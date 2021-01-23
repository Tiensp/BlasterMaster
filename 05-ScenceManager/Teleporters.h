#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "BulletTeleporter.h"

#define TELEPORTER_ANI_GRAY_MODE_ON 0
#define TELEPORTER_ANI_GRAY_MODE_OFF 1
#define TELEPORTER_ANI_TELEPORT 2
#define TELEPORTER_ANI_TELEPORT1 3
#define TELEPORTER_ANI_TELEPORT2 4
#define TELEPORTER_ANI_TELEPORT3 5
#define TELEPORTER_ANI_DEATH 6


#define TELEPORTER_BBOX_WIDTH 25
#define TELEPORTER_BBOX_HEIGHT 33
#define TELEPORTER_BBOX_HEIGHT_DIE 32

class CTeleporter : public Enemy
{
	LPGAMEOBJECT target;

	BulletObject* teleporter_bullet;

	int interval = 10;
	int timer;
	int jumpStep;
	float new_x, new_y;
	float old_x, old_y;

	bool isDoneDeath;
	bool isCollision;


public:
	CTeleporter(float x, float y, LPGAMEOBJECT playe, int _itemType);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	int RandomPosition();
	void flowPlayer(LPGAMEOBJECT player);
};




