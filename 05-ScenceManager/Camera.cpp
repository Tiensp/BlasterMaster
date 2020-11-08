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
	//Khởi tạo Vector4 từ Vector2
	D3DXVECTOR4(pos.x, pos.y, 1, 1);

	//Khởi tạo ma trận đơn vị
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);


	return D3DXVECTOR2();
}

/*D3DXVECTOR2 CCamera::World2Render(float x, float y)
{
	return D3DXVECTOR2(x - xCam, y - yCam);
}
*/
/*void CCamera::SetPosition(float x, float y)
{
	if (x <= boundLeft)
		xCam = boundLeft;
	else if (x > boundRight - width + W_CAM_BOUND)
		xCam = boundRight - width + W_CAM_BOUND;
	else
		xCam = x;
	yC = y;
}*/
