#include "Camera.h"
#include <cstddef>

CCamera* CCamera::__intance = NULL;

CCamera* CCamera::GetInstance()
{
	if (__intance == NULL)
		__intance = new CCamera(SCREEN_WIDTH, SCREEN_HEIGHT);
	return __intance;
}

CCamera::CCamera(int width, int height)
{
	this->width = width;
	this->height = height;

	//camPos = D3DXVECTOR3(0, 0, 0);
}

CCamera::~CCamera()
{
}

D3DXVECTOR2 CCamera::World2Render(const D3DXVECTOR2& pos)
{
	//Khởi tạo Vector4
	D3DXVECTOR4 vp_pos;

	//Khởi tạo ma trận đơn vị
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = -1.0f;
	mt._41 = -camPos.x;
	mt._42 = camPos.y;

	D3DXVec3Transform(&vp_pos, &D3DXVECTOR3(pos.x, pos.y, 1), &mt);
	D3DXVECTOR2 _pos(vp_pos.x, vp_pos.y);

	return _pos;
}

void CCamera::SetPosition(D3DXVECTOR2 pos)
{
	camPos.x = pos.x;
	camPos.y = pos.y;
}


