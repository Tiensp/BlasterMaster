#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Sophia.h"
#include "Goomba.h"
#include "Koopas.h"
#include "Map.h"
#include "GameDefine.h"


class CPlayScene: public CScene
{
protected: 
	CSophia *player;	// A play scene has to have player, right? 
	CMap* map;			//Cần một đối tượng lưu trữ MAP
	CCamera* camera;	//Và một đối tượng lưu trữ camera của Play Scene

	vector<LPGAMEOBJECT> objects;	//một list obj lưu trữ các GameObj có trong Play Scene

	/* Các hàm ParsSection dùng để đọc file */
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAP(string line);

	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();


	CSophia * GetPlayer() { return this->player; } 
	CCamera* GetCamera() { return this->camera; }
	CMap* GetMap() { return this->map; }
	//friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public: 
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

