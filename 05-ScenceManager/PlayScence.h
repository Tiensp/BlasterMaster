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
#include "Floaters.h"
#include "Skulls.h"
#include "Ship.h"
#include "Orbs.h"
#include "BulletFloaters.h"
#include "BulletSkull.h"
#include "BulletShip.h"
#include "BulletEyeball.h"
#include "Insect.h"
#include "MiniScene.h"
#include "Portal.h"
#include "Eyeballs.h"
#include "Teleporters.h"
#include "Cannons.h"
#include "Lava.h"
#include "ThornOVERHEAD.h"
#include "ThornOVERWORLD.h"
#include "RockOVH.h"
#include "Item.h"
#include "Grid.h"
#include "Ladder.h"

class CPlayScene: public CScene
{
protected: 
	CSophia *sophia;	// A play scene has to have player, right? 
	CJason *jason;
	CBigJason *bigJason;

	CMap* map;			//Cần một đối tượng lưu trữ MAP
	CCamera* camera;	//Và một đối tượng lưu trữ camera của Play Scene
	HUD* hud;
	CGrid *grid;

	
	vector<LPGAMEOBJECT> AllObjs;
	vector<LPGAMEOBJECT> objects;	//một list obj lưu trữ các GameObj có trong Play Scene
	vector<LPGAMEOBJECT> listEnemies;
	vector<LPBulletObject> listBullet;
	vector<LPBulletObject> bulletFloater;
	vector<LPBulletObject> bulletSkull;
	vector<LPBulletObject> bulletShip;
	vector<LPBulletObject> bulletEyeball;
	vector<MiniScene*>	listScene;
	vector<LPGAMEOBJECT> listPortal;
	
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
	vector<MiniScene*> GetlistScenes() { return listScene; }
	void ClassifyOBJECT(vector<LPGAMEOBJECT> obj);	//Phân loại các obj
	
	//////// PUBLIC VARIABLE //////////
	int currentMiniScene;
	bool isSelectBulletScr = false;
	int currentSELECT = 0;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public: 
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

