﻿#pragma once
#include "Game.h"
#include "GameDefine.h"
#include "GameObject.h"


class CCamera
{
	static CCamera* __intance;

	D3DXVECTOR2 camPos;

	int width;		
	int height;

	RECT camBound;		  //Set biên giới hạn camera dựa vào kích thước map
	
	//LPGAMEOBJECT gameObj; //Lưu gameObj camera follow

public:
	static CCamera* GetInstance();
	CCamera(int w, int h);
	~CCamera();
	D3DXVECTOR2 World2Cam(const D3DXVECTOR2& pos);
	D3DXVECTOR2 Cam2World(const D3DXVECTOR2& pos);

	void SetPosition(const D3DXVECTOR2& pos);
	void SetDefaultCam();
	D3DXVECTOR2 GetCamPos() { return camPos; }

	bool isContain(RECT rect);

	int GetWidth() { return this->width; }
	int GetHeight() { return this->height; }
	RECT GetCamBound();
	void SetBoundSize(float _w, float _h);

	//void SetGameObject(LPGAMEOBJECT gameObj) { this->gameObj = gameObj; }

	bool IsAutoCam();
	void AutoCamX(float _distance, int direct);
	void UpdateAutoCam(DWORD dt);
	void LockCam();
	void UnlockCam();
	void SetCamBound(float mapWidth, float mapHeight);
	void Update();
};



