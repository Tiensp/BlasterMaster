#include "Camera.h"
#include <cstddef>
#include "Sophia.h"
#include "Jason.h"
#include "BigJason.h"
#include "PlayScence.h"

#define PULL_SCREEN_Y	44

CCamera* CCamera::__instance = NULL;

CCamera* CCamera::GetInstance()
{
	if (__instance == NULL)
	{
		__instance = new CCamera(CAMERA_WIDTH, CAMERA_HEIGHT);
	}
		
	return __instance;
}

CCamera::CCamera(int width, int height)
{
	this->width = width;
	this->height = height;
	isSwitchScene = false;
}

CCamera::~CCamera()
{
}

D3DXVECTOR2 CCamera::World2Cam(const D3DXVECTOR2& pos)
{
	/* 
		Ban đầu mình sử dụng code dưới đây để transform tọa độ vì nó XỊN =)))
		và lúc tìm hiểu mình được biết transform bằng cách nhân vector với ma trận 
		tốt hơn vì máy trính thực hiện phép nhân chia nhanh hơn cộng trừ (mình không sure nhe)

		Tuy nhiên về sau mình nhận ra khi render, việc gọi hàm này liên tục mỗi khi vẽ
		và phải chạy đi chạy lại mớ code này còn khiên chương trình chậm và lag hơn nên quyết 
		định không sử dụng nữa.
	*/

	/*
		//Khởi tạo Vector4
		D3DXVECTOR4 vp_pos;

		//Khởi tạo ma trận đơn vị
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		mt._41 = -camPos.x;
		mt._42 = -camPos.y;

		D3DXVec3Transform(&vp_pos, &D3DXVECTOR3(pos.x, pos.y, 1), &mt);
		D3DXVECTOR2 _pos(vp_pos.x, vp_pos.y);
	*/
	return D3DXVECTOR2(pos.x - camPos.x, pos.y - camPos.y);
}

D3DXVECTOR2 CCamera::Cam2World(const D3DXVECTOR2& pos)
{
	return D3DXVECTOR2(pos.x + camPos.x, pos.y + camPos.y);
}

void CCamera::SetPosition(const D3DXVECTOR2 &pos)
{
	camPos.x = pos.x;
	camPos.y = pos.y;
}

bool CCamera::isContain(RECT rect)
{
	//Lấy biên giới hạn camera
	RECT camRect;
	camRect.left = camPos.x;
	camRect.top = camPos.y;
	camRect.right = camPos.x + width;
	camRect.bottom = camPos.y + height;

	//Kiểm tra rect có giao với Camera hay không
	if (rect.left > camRect.right || rect.right < camRect.left || rect.top > camRect.bottom || rect.bottom < camRect.top)
	{
		return false;
	}

	return true;
}

bool CCamera::isContain(D3DXVECTOR2 pos)
{
	//Lấy biên giới hạn camera
	RECT camRect;
	camRect.left = camPos.x;
	camRect.top = camPos.y;
	camRect.right = camPos.x + width;
	camRect.bottom = camPos.y + height;

	//Kiểm tra Pos có nằm trong Camera hay không
	if (pos.x > camRect.right || pos.x < camRect.left || pos.y > camRect.bottom || pos.y < camRect.top)
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

void CCamera::Update()
{
	if (!isSwitchScene)
	{
		D3DXVECTOR2 playerPos;
		if (_ACTIVE[SOPHIA])
			CSophia::GetInstance()->GetPosition(playerPos.x, playerPos.y);
		else if (_ACTIVE[JASON])
		{
			CJason::GetInstance()->GetPosition(playerPos.x, playerPos.y);
		}
		else if (_ACTIVE[BIG_JASON])
			CBigJason::GetInstance()->GetPosition(playerPos.x, playerPos.y);

		if (playerPos.x > camPos.x + width * 0.55)
			camPos.x += playerPos.x - (camPos.x + width * 0.55);
		else if (playerPos.x < camPos.x + width * 0.35)
			camPos.x -= (camPos.x + width * 0.35) - playerPos.x;

		if (playerPos.y > camPos.y + height * 0.75)
			camPos.y += playerPos.y - (camPos.y + height * 0.75);
		else if (playerPos.y < camPos.y + height * 0.25)
			camPos.y -= (camPos.y + height * 0.25) - playerPos.y;

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

		if (camPos.x > camBound.right - width)
			camPos.x = camBound.right - width;

		if (camPos.y > camBound.bottom - height /*+ PULL_SCREEN_Y*/)
			camPos.y = camBound.bottom - height /*+ PULL_SCREEN_Y*/;
	}
	else
	{
		if (camPos.x != SwitchScenePos.x)
			if (camPos.x > SwitchScenePos.x)
				camPos.x -= 2.0f;
			else
				camPos.x += 2.0f;
		else
		{
			isSwitchScene = false;
		}
	}
}

void CCamera::SetCamBound(float x, float y, float mapWidth, float mapHeight)
{
	camBound.left = x;
	camBound.top = y;
	camBound.right = x + mapWidth;
	camBound.bottom = y + mapHeight;
}
