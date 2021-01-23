#pragma once
#include "BulletObject.h"
#include "Brick.h"
#include "Sophia.h"

class BulletTeleporter : public BulletObject
{

protected:
	CSophia* sophia;

	int followPlayer = 1;

	LPGAMEOBJECT target;
public:
	BulletTeleporter(float _start_x, float y_start_y, LPGAMEOBJECT player);
	~BulletTeleporter();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetState(int state);
};

