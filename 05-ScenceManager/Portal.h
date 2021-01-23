#pragma once
#include "GameObject.h"
#include "GameDefine.h"


class CPortal;
typedef CPortal* LPPORTAL;
/*
	Object that triggers scene switching
*/
class CPortal : public CGameObject
{
	int scene_id;	// Scene chứa portal này
	int portal_id;	// Thứ tự của portal trong scene
	int des_scene;	// Scene mục tiêu sẽ dịch chuyển đến
	
	

public:
	CPortal(float _x, float _y, int sceneID, int portalID, int desScene, int _nx, int type, float x_des, float y_des);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	int GetSceneId() { return scene_id;  }
	int GetPortalID() { return portal_id; }
	int GetDesScene() { return des_scene; }

	float x_render;	//Tọa độ render của portal
	float y_render;

	float x_des;	//Tọa độ đích(destination) cần chuyển đến khi nhân vật chạm portal
	float y_des;

	int width;
	int height;

};