//#include "BulletFloaters.h"
//
//BulletFloaters::BulletFloaters(float x, float y)
//{
//	/*vx = 0.5f;
//	vy = 0.5f;*/
//	this->x = x;
//	this->y = y;
//	aniBullet = CAnimations::GetInstance()->Get(BULLET_FLOATERS_ANI);
//	
//}
//
//BulletFloaters::~BulletFloaters()
//{
//}
//
//void BulletFloaters::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
//{
//	//BulletObject::Update(dt, coObjects);
//	this->dt = dt;
//	dx = 0.05f * dt;
//	//dy = 0.05f * dt;
//	x += dx;
//	y += dy;
//
//	
//
//
//}
//
//void BulletFloaters::Render()
//{
//	RenderBoundingBox();
//	aniBullet->Render(x,y);
//
//
//}
//
//void BulletFloaters::GetBoundingBox(float& left, float& top, float& right, float& bottom)
//{
//	left = x;
//	top = y;
//	right = x + 10;
//	bottom = y + 10;
//	
//}
