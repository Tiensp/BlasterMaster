
#pragma once
#include "GameObject.h"

struct BulletObject;
typedef BulletObject* LPBulletObject;
class BulletObject : public CGameObject
{
public:
	float x_Border, y_Border;
	bool isMove = false;
	LPANIMATION aniBullet;
public:
	BulletObject();
	~BulletObject();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	void Set_IsMove(const bool& _isMove);
	void HandleMove(const float& x_border, const float& y_border);
	virtual void Render();


};

