#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"


using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_MAP	7

#define OBJECT_TYPE_SOPHIA	0
#define OBJECT_TYPE_JASON	1
#define OBJECT_TYPE_BIG_JASON 2
#define OBJECT_TYPE_BRICK	3
#define OBJECT_TYPE_GOLEM	4
#define	OBJECT_TYPE_DOMES	5
#define OBJECT_TYPE_WORMS 6
#define OBJECT_TYPE_FLOATERS 7
#define OBJECT_TYPE_SKULLS 8
#define OBJECT_TYPE_INSECT 9
#define OBJECT_TYPE_ORB 10
#define OBJECT_TYPE_SHIP 11
#define OBJECT_TYPE_EYEBALL 12
#define OBJECT_TYPE_CANNON 14


#define OBJECT_TYPE_PORTAL	52
#define OBJECT_TYPE_SCENE 53

#define MAX_SCENE_LINE 1024


void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations *animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());
		
		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_SOPHIA:
	{
		if (sophia != NULL)
		{
			DebugOut(L"[ERROR] SOPHIA object was created before!\n");
			return;
		}


		obj = CSophia::GetInstance();
		sophia = (CSophia*)obj;
		sophia->SetStartPos(x, y);
		bool active = atoi(tokens[4].c_str());
		_ACTIVE[SOPHIA] = active;

		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		objects.push_back(obj);
		DebugOut(L"[INFO] SOPHIA object created!\n");
	}
	break;
	case OBJECT_TYPE_JASON:
	{
		if (jason != NULL)
		{
			DebugOut(L"[ERROR] JASON object was created before!\n");
			return;
		}

		obj = CJason::GetInstance();
		jason = (CJason*)obj;
		jason->SetStartPos(x, y);
		bool active = atoi(tokens[4].c_str());
		_ACTIVE[JASON] = active;

		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		objects.push_back(obj);
		DebugOut(L"[INFO] JASON object created!\n");
	}
	break;
	case OBJECT_TYPE_BIG_JASON:
	{
		if (bigJason != NULL)
		{
			DebugOut(L"[ERROR] BIG JASON object was created before!\n");
			return;
		}

		obj = CBigJason::GetInstance();
		bigJason = (CBigJason*)obj;
		bigJason->SetStartPos(x, y);
		bool active = atoi(tokens[4].c_str());
		_ACTIVE[BIG_JASON] = active;

		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		objects.push_back(obj);
		DebugOut(L"[INFO] BIG JASON object created!\n");
	}
	break;
	case OBJECT_TYPE_BRICK:
	{
		float w = atof(tokens[4].c_str());
		float h = atof(tokens[5].c_str());
		obj = new CBrick(x, y, w, h);
		obj->SetPosition(x, y);
		objects.push_back(obj);
		break;
	}
	case OBJECT_TYPE_GOLEM:
	{
		obj = new CGolem(x, y, sophia);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		listEnemies.push_back(obj);

		break;

	}
	case OBJECT_TYPE_DOMES:
	{
		obj = new CDomes(x, y, 999999, 999999, sophia);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		listEnemies.push_back(obj);
		break;

	}
	case OBJECT_TYPE_WORMS:
	{
		obj = new CWorm(x, y, sophia);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		listEnemies.push_back(obj);
		break;
	}
	break;
	case OBJECT_TYPE_FLOATERS:
	{
		obj = new CFloaters(x, y, sophia);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		listEnemies.push_back(obj);
		break;
	}
	case OBJECT_TYPE_SKULLS:
	{
		obj = new CSkull(x, y, sophia);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		listEnemies.push_back(obj);
		break;
	}
	case OBJECT_TYPE_INSECT:
	{
		obj = new CInsect(x, y, sophia);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		listEnemies.push_back(obj);
		break;
	}
	case OBJECT_TYPE_ORB:
	{
		obj = new COrb(x, y, sophia);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		listEnemies.push_back(obj);
		break;
	}
	case OBJECT_TYPE_SHIP:
	{
		obj = new CShip(x, y, sophia);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		listEnemies.push_back(obj);
		break;
	}

	case OBJECT_TYPE_EYEBALL:
	{
		obj = new CEyeballs(x, y, sophia);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		listEnemies.push_back(obj);
		break;
	}

	case OBJECT_TYPE_CANNON:
	{
		obj = new CCannon(x, y, sophia);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		listEnemies.push_back(obj);
		break;
	}

	case OBJECT_TYPE_PORTAL:
	{
		int sceneID = atoi(tokens[3].c_str());
		int porID = atoi(tokens[4].c_str());
		int dir = atoi(tokens[5].c_str());
		int type = atoi(tokens[6].c_str());
		float xDes = atof(tokens[7].c_str());
		float yDes = atof(tokens[8].c_str());
		ani_set_id = atoi(tokens[9].c_str());
		obj = new CPortal(x, y, sceneID, porID, dir, type, xDes, yDes);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		listPortal.push_back(obj);
		break;
	}
	case OBJECT_TYPE_SCENE:
	{
		int sceneID = atoi(tokens[4].c_str());
		int width = atoi(tokens[5].c_str());
		int height = atoi(tokens[6].c_str());
		MiniScene* miniS = new MiniScene(sceneID, x, y, width, height);
		listScene.push_back(miniS);
		break;
	}
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup

}

void CPlayScene::_ParseSection_MAP(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines

	int map_id = atoi(tokens[0].c_str());
	string pathMatrix = tokens[1];
	string pathTileSet = tokens[2];

	map = new CMap(map_id, pathMatrix, pathTileSet);
}

/*
	LOAD PLAYSCENE
*/
void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line == "[MAP]") {
			section = SCENE_SECTION_MAP; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_MAP: _ParseSection_MAP(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
	
	// Khởi tạo camera
	MiniScene* miniScene = listScene.at(1);
	camera = CCamera::GetInstance();
	camera->SetCamBound(miniScene->x, miniScene->y, miniScene->width, miniScene->height);
	//camera->SetCamBound(0, 0, map->GetMapWidth(), map->GetMapHeight());


	//Thiết lập trạng thái, vị trí khởi đầu,... cho đối tượng đang active
	if (_ACTIVE[SOPHIA])
		sophia->Reset();
	else if (_ACTIVE[JASON])
		jason->Reset();
	else if (_ACTIVE[BIG_JASON])
		bigJason->Reset();
	//Sau khi active và khởi tạo xong xong đối tượng player thì khởi tạo thanh HUD 
	hud = new HUD();
	
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Sophia is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;

	DebugOut(L"size %d\n", listBulletPlayer.size());
	for (int i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	
	}
	for (int i = 0; i < listEnemies.size(); i++)
	{
		coObjects.push_back(listEnemies[i]);
		if (dynamic_cast<CFloaters*>(listEnemies[i]))
		{
			CFloaters* floater = dynamic_cast<CFloaters*>(listEnemies[i]);
			bulletFloater = floater->Get_Bullet_List();

		}
	}
	for (int i = 0; i < listPortal.size(); i++)
	{
		coObjects.push_back(listPortal[i]);
	}

	

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}
	listBullet = sophia->Get_Bullet_List();
	for (int i = 0; i < listEnemies.size(); i++)
		listEnemies[i]->Update(dt, &coObjects);
	for (int i = 0; i < listEnemies.size(); i++)
	{
		coObjects.push_back(listEnemies[i]);
		if (dynamic_cast<CFloaters*>(listEnemies[i]))
		{
			CFloaters* floater = dynamic_cast<CFloaters*>(listEnemies[i]);
			bulletFloater = floater->Get_Bullet_List();
		}
	}

	for (int i = 0; i < listBullet.size(); i++)
	{
		listBullet[i]->Update(dt, &coObjects);
		
	}
	for (int i = 0; i < bulletFloater.size(); i++)
	{
		bulletFloater[i]->Update(dt, &coObjects);
	}

		
	// skip the rest if scene was already unloaded (Sophia::Update might trigger PlayScene::Unload)
	//if (sophia == NULL && jason == NULL && bigJason == NULL) return;

	// Update camera to follow player
	camera->Update();
	//Update HUD
	hud->Update();

}

void CPlayScene::Render()
{
	map->DrawMap();
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
	for (int i = 0; i < listEnemies.size(); i++)
		listEnemies[i]->Render();
	for (int i = 0; i < listPortal.size(); i++)
		listPortal[i]->Render();
	for (int i = 0; i < listBullet.size(); i++)
		listBullet[i]->Render();
	for (int i = 0; i < bulletFloater.size(); i++)
		bulletFloater[i]->Render();
	hud->Render();
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	sophia = NULL;
	jason = NULL;
	bigJason = NULL;
	map = NULL;
	camera = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_I:
		{
			_ACTIVE[SOPHIA] = true;
			_ACTIVE[JASON] = false;
			_ACTIVE[BIG_JASON] = false;
			CSophia::GetInstance()->Reset();
		}
		break;
	case DIK_O:
		{
			_ACTIVE[SOPHIA] = false;
			_ACTIVE[JASON] = true;
			_ACTIVE[BIG_JASON] = false;
			CJason::GetInstance()->Reset();
		}
		break;
	case DIK_P:
		{
			_ACTIVE[SOPHIA] = false;
			_ACTIVE[JASON] = false;
			_ACTIVE[BIG_JASON] = true;
			CBigJason::GetInstance()->Reset();
		}
		break;
	case DIK_M:
	{
		CCamera* camera = CCamera::GetInstance();
		camera->isSwitchScene = true;
		D3DXVECTOR2 camPos = camera->GetCamPos();
		camera->SwitchScenePos = D3DXVECTOR2(camPos.x - camera->GetWidth(), camPos.y);
		break;
	}
	case DIK_N:
	{
		CCamera* camera = CCamera::GetInstance();
		camera->isSwitchScene = true;
		D3DXVECTOR2 camPos = camera->GetCamPos();
		camera->SwitchScenePos = D3DXVECTOR2(camPos.x + camera->GetWidth(), camPos.y);
		break;
	}
	case DIK_B:
	{
		if (_ACTIVE[SOPHIA])
		{
			CPlayScene* scene = ((CPlayScene*)scence);
			MiniScene* miniScene = scene->GetListScene().at(0);
			CCamera* camera = CCamera::GetInstance();
			camera->SetCamBound(miniScene->x, miniScene->y, miniScene->width, miniScene->height);
			CSophia* sophia = CSophia::GetInstance();
			sophia->SetStartPos(1100, 800);
			sophia->Reset();

			break;
		}
	}

	}
	if (_ACTIVE[SOPHIA])
	{
		CSophia* sophia = ((CPlayScene*)scence)->GetSophia();
		_KEYCODE[KeyCode] = true;
		sophia->OnKeyDown(KeyCode);
	}
	else if (_ACTIVE[JASON])
	{
		CJason* jason = ((CPlayScene*)scence)->GetJason();
		_KEYCODE[KeyCode] = true;
		jason->OnKeyDown(KeyCode);
	}
	else if (_ACTIVE[BIG_JASON])
	{
		CBigJason* bigJason = ((CPlayScene*)scence)->GetBigJason();
		_KEYCODE[KeyCode] = true;
		bigJason->OnKeyDown(KeyCode);
	}
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	
	if (_ACTIVE[SOPHIA])
	{
		CSophia* sophia = ((CPlayScene*)scence)->GetSophia();
		_KEYCODE[KeyCode] = false;
		sophia->OnKeyUp(KeyCode);
	}
	else if (_ACTIVE[JASON])
	{
		CJason* jason = ((CPlayScene*)scence)->GetJason();
		_KEYCODE[KeyCode] = false;
		jason->OnKeyUp(KeyCode);
	}
	else if (_ACTIVE[BIG_JASON])
	{
		CBigJason* bigJason = ((CPlayScene*)scence)->GetBigJason();
		_KEYCODE[KeyCode] = false;
		bigJason->OnKeyUp(KeyCode);
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	

	// disable control key when Sophia die 
	/*if (sophia->GetState() == SOPHIA_STATE_DIE) return;*/

}