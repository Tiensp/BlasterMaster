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
	
}

CCamera::~CCamera()
{
}

D3DXVECTOR2 CCamera::World2Cam(const D3DXVECTOR2& pos)
{
	//Khởi tạo Vector4
	D3DXVECTOR4 vp_pos;

	//Khởi tạo ma trận đơn vị
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._41 = -camPos.x;
	mt._42 = -camPos.y;

	D3DXVec3Transform(&vp_pos, &D3DXVECTOR3(pos.x, pos.y, 1), &mt);
	D3DXVECTOR2 _pos(vp_pos.x, vp_pos.y);

	return _pos;
}

D3DXVECTOR2 CCamera::Cam2World(const D3DXVECTOR2& pos)
{
	//Khởi tạo Vector4
	D3DXVECTOR4 vp_pos;

	//Khởi tạo ma trận đơn vị			
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._41 = camPos.x;
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

bool CCamera::isContain(RECT rect)
{
	//Lấy biên giới hạn camera
	RECT camRect = GetCamBound();
	//Kiểm tra rect có giao với Camera hay không
	if (rect.left > camRect.right || rect.right < camRect.left || rect.top > camRect.bottom || rect.bottom < camRect.top)
	{
		return false;
	}

	return true;
}

void CCamera::Update()
{
	
}

RECT CCamera::GetCamBound()
{
	camBound.left = camPos.x;
	camBound.top = camPos.y;
	camBound.right = camPos.x + width;
	camBound.bottom = camPos.y + height;
	return camBound;
}
