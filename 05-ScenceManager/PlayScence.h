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
#include "Golem.h"
#include "Domes.h"
#include "GameDefine.h"
#include "Worms.h"
#include "BulletObject.h"
#include "HUD.h"


class CPlayScene: public CScene
{
protected: 
	CSophia *sophia;	// A play scene has to have player, right? 
	CJason *jason;
	CBigJason *bigJason;

	CMap* map;			//Cần một đối tượng lưu trữ MAP
	CCamera* camera;	//Và một đối tượng lưu trữ camera của Play Scene
	HUD* hud;
	vector<LPGAMEOBJECT> objects;	//một list obj lưu trữ các GameObj có trong Play Scene
	vector<LPGAMEOBJECT> listEnemies;
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


	CSophia * GetSophia() { return this->sophia; }
	CJason* GetJason() { return this->jason; }
	CBigJason* GetBigJason() { return this->bigJason; }
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

