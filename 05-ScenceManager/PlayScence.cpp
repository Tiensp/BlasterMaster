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
#define SCENE_SECTION_OBJECTS	0
#define SCENE_SECTION_MAP	1

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
#define OBJECT_TYPE_TELEPORTER 13
#define OBJECT_TYPE_CANNON 14
#define OBJECT_TYPE_ITEM 80
#define OBJECT_TYPE_LADDER 49

#define OBJECT_TYPE_LAVA 90
#define OBJECT_TYPE_THORN_OVERWORLD 91
#define OBJECT_TYPE_THORN_OVERHEAD 92
#define OBJECT_TYPE_ROCK_OVERHEAD 93

#define OBJECT_TYPE_BOSS 100


#define OBJECT_TYPE_PORTAL	84
#define OBJECT_TYPE_SCENE 53

#define MAX_SCENE_LINE 1024


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


		obj = INSTANCE_SOPHIA;
		sophia = (CSophia*)obj;
		sophia->SetStartPos(x, y);
		bool active = atoi(tokens[4].c_str());
		_ACTIVE[SOPHIA] = active;
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		AllObjs.push_back(obj);
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

		obj = INSTANCE_JASON;
		jason = (CJason*)obj;
		jason->SetStartPos(x, y);
		bool active = atoi(tokens[4].c_str());
		_ACTIVE[JASON] = active;

		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		AllObjs.push_back(obj);
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

		obj = INSTANCE_BIGJASON;
		bigJason = (CBigJason*)obj;
		bigJason->SetStartPos(x, y);
		bool active = atoi(tokens[4].c_str());
		_ACTIVE[BIG_JASON] = active;

		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		AllObjs.push_back(obj);
		DebugOut(L"[INFO] BIG JASON object created!\n");
	}
	break;
	case OBJECT_TYPE_BRICK:
	{
		float w = atof(tokens[4].c_str());
		float h = atof(tokens[5].c_str());
		obj = new CBrick(x, y, w, h);
		obj->SetPosition(x, y);
		AllObjs.push_back(obj);
		break;
	}
	case OBJECT_TYPE_LADDER:
	{
		float w = atof(tokens[4].c_str());
		float h = atof(tokens[5].c_str());
		obj = new CLadder(x, y, w, h);
		obj->SetPosition(x, y);
		AllObjs.push_back(obj);
		break;
	}
	case OBJECT_TYPE_GOLEM:
	{
		obj = new CGolem(x, y, sophia);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		AllObjs.push_back(obj);

		break;

	}
	case OBJECT_TYPE_DOMES:
	{
		obj = new CDomes(x, y, 999999, 999999, sophia);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		AllObjs.push_back(obj);
		break;

	}
	case OBJECT_TYPE_WORMS:
	{
		obj = new CWorm(x, y, sophia);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		AllObjs.push_back(obj);
		break;
	}
	break;
	case OBJECT_TYPE_FLOATERS:
	{
		obj = new CFloaters(x, y, sophia);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		AllObjs.push_back(obj);
		break;
	}
	case OBJECT_TYPE_SKULLS:
	{
		obj = new CSkull(x, y, sophia);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		AllObjs.push_back(obj);
		break;
	}
	case OBJECT_TYPE_INSECT:
	{
		obj = new CInsect(x, y, sophia);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		AllObjs.push_back(obj);
		break;
	}
	case OBJECT_TYPE_ORB:
	{
		obj = new COrb(x, y, sophia);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		AllObjs.push_back(obj);
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

	case OBJECT_TYPE_TELEPORTER:
	{
		obj = new CTeleporter(x, y, sophia);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
	/*	AllObjs.push_back(obj);*/
		break;
	}

	case OBJECT_TYPE_CANNON:
	{
		obj = new CCannon(x, y, sophia);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		AllObjs.push_back(obj);
		break;
	}

	case OBJECT_TYPE_LAVA:
	{
		float w = atof(tokens[4].c_str());
		float h = atof(tokens[5].c_str());
		obj = new CLava(x, y, w, h);
		obj->SetPosition(x, y);
		objects.push_back(obj);
		break;
	}

	case OBJECT_TYPE_THORN_OVERWORLD:
	{
		float w = atof(tokens[4].c_str());
		float h = atof(tokens[5].c_str());
		obj = new CThornOVW(x, y, w, h);
		obj->SetPosition(x, y);
		objects.push_back(obj);
		break;
	}

	case OBJECT_TYPE_THORN_OVERHEAD:
	{
		float w = atof(tokens[4].c_str());
		float h = atof(tokens[5].c_str());
		obj = new CThornOVH(x, y, w, h);
		obj->SetPosition(x, y);
		objects.push_back(obj);
		break;
	}

	case OBJECT_TYPE_ROCK_OVERHEAD:
	{
		obj = new CRockOVH(x, y,16,16);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		AllObjs.push_back(obj);
		break;
	}
	case OBJECT_TYPE_ITEM:
	{
		int type = atoi(tokens[4].c_str());
		obj = new CItem(type);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		AllObjs.push_back(obj);
		break;
	}
	case OBJECT_TYPE_PORTAL:
	{
		int sceneID = atoi(tokens[3].c_str());
		int porID = atoi(tokens[4].c_str());
		int desScene = atoi(tokens[5].c_str());
		int dir = atoi(tokens[6].c_str());
		int type = atoi(tokens[7].c_str());
		float xDes = atof(tokens[8].c_str());
		float yDes = atof(tokens[9].c_str());
		ani_set_id = atoi(tokens[10].c_str());
		obj = new CPortal(x, y, sceneID, porID, desScene, dir, type, xDes, yDes);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		AllObjs.push_back(obj);
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
	case OBJECT_TYPE_BOSS:
	{
		obj = new CBoss(x, y, sophia);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		AllObjs.push_back(obj);
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
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_MAP: _ParseSection_MAP(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene objects %s\n", sceneFilePath);
	
	// Khởi tạo camera
	currentMiniScene = 0;
	MiniScene* miniScene = listScene.at(currentMiniScene);
	camera = CCamera::GetInstance();
	camera->SetCamBound(miniScene->x, miniScene->y, miniScene->width, miniScene->height);
	camera->SetPosition(D3DXVECTOR2(miniScene->x, miniScene->y));
	//camera->SetCamBound(0, 0, map->GetMapWidth(), map->GetMapHeight());

	grid = new CGrid(map->GetMapWidth(), map->GetMapHeight());
	for (int i = 0; i < AllObjs.size(); i++)
	{
		if (AllObjs.at(i)->objTag != PLAYER)
			grid->AddObject(AllObjs.at(i));
	}

	//Thiết lập trạng thái, vị trí khởi đầu,... cho đối tượng đang active
	if (_ACTIVE[SOPHIA])
	{
		sophia->Reset();
		grid->AddObject(sophia);
	}
		
	else if (_ACTIVE[JASON])
	{
		jason->Reset();
		grid->AddObject(jason);
	}
	else if (_ACTIVE[BIG_JASON])
	{
		bigJason->Reset();
		grid->AddObject(bigJason);
	}
	//Sau khi active và khởi tạo xong xong đối tượng player thì khởi tạo thanh HUD 
	hud = new HUD();

}

void CPlayScene::Update(DWORD dt)
{
	// We know that Sophia is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	if (!isSelectBulletScr)
	{
		vector<LPGAMEOBJECT> coObjects = grid->GetActiveObj();
		ClassifyOBJECT(coObjects);

		if (_ACTIVE[SOPHIA] && !sophia->GetIsFrozen())
		{
			sophia->Update(dt, &coObjects);
		}
		else if (_ACTIVE[JASON])
		{
			jason->Update(dt, &coObjects);
		}
		else if (_ACTIVE[BIG_JASON])
		{
			bigJason->Update(dt, &coObjects);
		}

		for (int i = 0; i < coObjects.size(); i++)
		{
			if (!dynamic_cast<CBrick*>(coObjects.at(i)) && !dynamic_cast<CPortal*>(coObjects.at(i)) && 
				!dynamic_cast<CLadder*>(coObjects.at(i)) && coObjects.at(i)->objTag != PLAYER)
			{
				coObjects.at(i)->Update(dt, &coObjects);
			}
		}

	// skip the rest if scene was already unloaded (Sophia::Update might trigger PlayScene::Unload)
	//if (sophia == NULL && jason == NULL && bigJason == NULL) return;

		// Update camera to follow player
		camera->Update();
		//Update HUD
		hud->Update();
		//Grid Update
		grid->Update(coObjects);
	}
	else
	{
		/// Update màn hình chọn đạn
		
	}

}

void CPlayScene::Render()
{
	if (!isSelectBulletScr)
	{
		map->DrawMap();
		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();
		for (int i = 0; i < listEnemies.size(); i++)
			listEnemies[i]->Render();
		// Thứ tự Render của Player chỉ sau Portal và Enemy
		if (_ACTIVE[SOPHIA])
		{
			sophia->Render();
		}

		if (_ACTIVE[JASON])
		{
			jason->Render();
		}

		if (_ACTIVE[BIG_JASON])
		{
			bigJason->Render();
		}

		for (int i = 0; i < listPortal.size(); i++)
			listPortal[i]->Render();
		/*for (int i = 0; i < listBullet.size(); i++)
			listBullet[i]->Render();*/
			/*for (int i = 0; i < bulletFloater.size(); i++)
				bulletFloater[i]->Render();*/
		hud->Render();

	}
	else
	{
		/// Render màn hình chọn đạn
		D3DXVECTOR2 camPos = camera->GetCamPos();
		LPANIMATION_SET aniSet = CAnimationSets::GetInstance()->Get(SELECT_BULLET);
		aniSet->at(currentSELECT)->Render(camPos.x, camPos.y);
	}
	
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

void CPlayScene::ClassifyOBJECT(vector<LPGAMEOBJECT> obj)
{
	objects.clear();
	listEnemies.clear();
	listPortal.clear();
	for (int i = 0; i < obj.size(); i++)
	{
		switch (obj.at(i)->objTag)
		{
		case ENEMY:
		{
			listEnemies.push_back(obj.at(i));
			break;
		}
		case PORTAL:
		{
			listPortal.push_back(obj.at(i));
			break;
		}
		case PLAYER:
			break;
		default:
		{
			objects.push_back(obj.at(i));
			break;
		}
		}
	}
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	/// KIỂM TRA XEM CÓ PHẢI ĐANG LÀ MÀN HÌNH CHỌN ĐẠN KHÔNG ?
	if (!((CPlayScene*)scence)->isSelectBulletScr)
	{
		CSophia* sophia = ((CPlayScene*)scence)->GetSophia();
		CJason* jason = ((CPlayScene*)scence)->GetJason();
		CBigJason* bigJason = ((CPlayScene*)scence)->GetBigJason();
		DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
		switch (KeyCode)
		{
		case DIK_I:
		{
			_ACTIVE[SOPHIA] = true;
			_ACTIVE[JASON] = false;
			_ACTIVE[BIG_JASON] = false;
			sophia->Reset();
		}
		break;
		case DIK_O:
		{
			_ACTIVE[SOPHIA] = false;
			_ACTIVE[JASON] = true;
			_ACTIVE[BIG_JASON] = false;
			jason->Reset();
		}
		break;
		case DIK_P:
		{
			_ACTIVE[SOPHIA] = false;
			_ACTIVE[JASON] = false;
			_ACTIVE[BIG_JASON] = true;
			bigJason->Reset();
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
				MiniScene* miniScene = scene->GetlistScenes().at(0);
				CCamera* camera = CCamera::GetInstance();
				camera->SetCamBound(miniScene->x, miniScene->y, miniScene->width, miniScene->height);
				CSophia* sophia = INSTANCE_SOPHIA;
				sophia->SetStartPos(1100, 800);
				sophia->Reset();

				break;
			}
		}
		/// Bấm W: Thì mở màn hình tạm dừng - chọn đạn
		case DIK_W:
		{
			((CPlayScene*)scence)->isSelectBulletScr = true;
			break;
		}
		}
		////////// KEY DOWN ///////////
		if (_ACTIVE[SOPHIA] && !sophia->GetIsFrozen())
		{
			CSophia* sophia = ((CPlayScene*)scence)->GetSophia();
			_KEYCODE[KeyCode] = true;
			if (!sophia->GetIsAutoGo())
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
	else
	{
		switch (KeyCode)
		{
		case DIK_RIGHT:
		{
			CPlayScene* plScene = ((CPlayScene*)scence);
			if (plScene->currentSELECT != 2)
			{
				plScene->currentSELECT++;
			}
			break;
		}
		case DIK_LEFT:
		{
			CPlayScene* plScene = ((CPlayScene*)scence);
			if (plScene->currentSELECT != 0)
			{
				plScene->currentSELECT--;
			}
			break;
		}
		case DIK_W:
		{
			((CPlayScene*)scence)->isSelectBulletScr = false;
			break;
		}
		}
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