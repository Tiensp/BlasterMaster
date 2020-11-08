#pragma once
#include "GameDefine.h"


class CCamera
{
	static CCamera* __intance;

	int xCam;
	int yCam;

	D3DXVECTOR2 camPos;

	int width;
	int height;

	float boundWidth;
	float boundHeight;
	float boundLeft;
	float boundRight;

public:
	static CCamera* GetInstance();
	CCamera(int w, int h);
	~CCamera();
	D3DXVECTOR2 World2Render(const D3DXVECTOR2 &pos);
	D3DXVECTOR2 Render2World(const D3DXVECTOR2& pos);
	void SetPosition(D3DXVECTOR2 pos);
	void SetDefaultCam();
	D3DXVECTOR2 GetCamPos() { return camPos; }
	float GetXCam();
	float GetYCam();
	int GetCurrentFloor();
	int GetWidth();
	int GetHeight();
	RECT GetRectCam();
	void SetBoundSize(float _w, float _h);
	float GetBoundHeight();
	float GetBoundWidth();
	void SetBoundLeftRight(float _l, float _r);
	void GetBoundLeftRight(float& _l, float& _r);
	bool IsContainCam(RECT rect);
	bool IsAutoCam();
	void AutoCamX(float _distance, int direct);
	void UpdateAutoCam(DWORD dt);
	void LockCam();
	void UnlockCam();
};



