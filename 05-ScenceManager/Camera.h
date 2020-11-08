#pragma once
#include "GameDefine.h"


class CCamera
{
	static CCamera* __intance;

	int xCam;
	int yCam;

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
	D3DXVECTOR2 Transform(float x, float y);
	void SetPosition(float x, float y);
	void SetDefaultCam();
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



