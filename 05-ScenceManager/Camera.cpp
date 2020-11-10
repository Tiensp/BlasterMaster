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

D3DXVECTOR2 CCamera::Transform(D3DXVECTOR2 pos)
{
	return D3DXVECTOR2(pos.x - xCam, pos.y - yCam);

}

RECT CCamera::GetBound()
{
	RECT bound;

	bound.left = (long)this->xCam;
	bound.right = (long)this->xCam +boundWidth;
	bound.top = (long)this->yCam;
	bound.bottom = (long)(this->yCam + boundHeight);

	return bound;
}

void CCamera::SetPosition(D3DXVECTOR2 pos)
{
	if (pos.x <= 0)
		camPos.x = 0;
	else if (pos.x > boundRight - width + W_CAM_BOUND)
		camPos.x = boundRight - width + W_CAM_BOUND;
	else
		camPos.x = pos.x;

	camPos.x = pos.x;
	camPos.y = pos.y;
}

void CCamera::SetBoundLeftRight(float _l, float _r)
{
	boundLeft = _l;
	boundRight = _r;
}
