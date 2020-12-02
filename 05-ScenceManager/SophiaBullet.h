#include "BulletObject.h"
#include "Enemy.h"
#include "Brick.h"

class SophiaBullet : public BulletObject
{
public:
	SophiaBullet() {};
	SophiaBullet(float _start_x, float _start_y);
	~SophiaBullet();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();
};
