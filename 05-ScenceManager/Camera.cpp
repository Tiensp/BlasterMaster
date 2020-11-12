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
	
	camBound.left = 0;
	camBound.top = 0;
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

RECT CCamera::GetCamBound()
{
	camBound.left = camPos.x;
	camBound.top = camPos.y;
	camBound.right = camPos.x + width;
	camBound.bottom = camPos.y + height;
	return camBound;
}

void CCamera::Update(CGameObject* gameObj)
{
	/*
		Kiểm tra xem Camera có bị vượt ra ngoài map không
		Vượt quá giới hạn thì đặt lại vị trí Camera

		Tọa độ biên trái và biên trên chắc chắn là tọa độ pos(0,0) 
		Cách xét tọa độ biên phải và biên dưới là tùy theo mỗi người
		Ở đây, tọa độ giới hạn của cam được tính theo:
			+ Tọa độ Biên phải - Độ dài Camera
			+ Tọa độ Biên dưới - Chiều cao Camera
	*/
	if (camPos.x < camBound.left)
		camPos.x = camBound.left;

	if (camPos.y < camBound.top)
		camPos.y = camBound.top;

	if (camPos.x > camBound.right - width + 14)
		camPos.x = camBound.right - width + 14;

	if (camPos.y > camBound.bottom - height + 35)
		camPos.y = camBound.bottom - height + 35;
}

void CCamera::SetCamBound(float mapWidth, float mapHeight)
{
	camBound.left = 0;
	camBound.top = 0;
	camBound.right = mapWidth;
	camBound.bottom = mapHeight;
}
