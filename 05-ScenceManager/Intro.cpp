#include <iostream>
#include <fstream>

#include "Intro.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"



using namespace std;

CIntro::CIntro(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CIntroKeyHandler(this);
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

#define MAX_SCENE_LINE 1024


void CIntro::_ParseSection_TEXTURES(string line)
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

void CIntro::_ParseSection_SPRITES(string line)
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

void CIntro::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CIntro::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations* animations = CAnimations::GetInstance();

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
void CIntro::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;

	switch (object_type)
	{
	/*case OBJECT_TYPE_ITEM:
	{
		int type = atoi(tokens[4].c_str());
		obj = new CItem(type);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		AllObjs.push_back(obj);
		break;
	}*/
	
	/*case OBJECT_TYPE_SCENE:
	{
		int sceneID = atoi(tokens[4].c_str());
		int width = atoi(tokens[5].c_str());
		int height = atoi(tokens[6].c_str());
		
		break;
	}*/
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup

}

/*
	LOAD Intro
*/
void CIntro::Load()
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
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);

	/// <summary>
	/// Khởi tạo camera & AniSet
	/// </summary>
	camera = CCamera::GetInstance();
	camera->SetCamBound(0, 0, 260, 260);
	camera->SetPosition(D3DXVECTOR2(0, 0));

	aniSet = CAnimationSets::GetInstance()->Get(SCENE_TYPE_TITLE_SCENE);
}

void CIntro::Update(DWORD dt)
{
	ChangeAniSet();
}

void CIntro::Render()
{
	if (!playRollOutScene)
	{
		if (aniSet->size() == 1)
		{
			// Nếu aniSet chỉ có 1 ani thì render ani đó (không thay đổi biến "curAniID")
			curAniID = 0;
			currentAni = aniSet->at(curAniID);
			currentAni->Render(0, 0);
		}
		else if (curAniID < aniSet->size())
		{
			// Render BackGround
			int randColor = rand() % 3; 
			int alpha = 255;
			D3DCOLOR purple = D3DCOLOR_ARGB(alpha, 120,29, 177);
			D3DCOLOR Green = D3DCOLOR_ARGB(alpha, 206, 0, 6);
			D3DCOLOR Grey = D3DCOLOR_ARGB(alpha, 255, 253, 49);
			CSprites::GetInstance()->Get(ID_BACKGROUND)->Draw(0, 0, 
				randColor == 0 ? purple : randColor == 1 ?
				Green : Grey);
			CSprites::GetInstance()->Get(ID_KHUNG_VIEN)->Draw(0, 0);

			currentAni = aniSet->at(curAniID);
			//Nếu là frame cuối cùng thì chỉ render frame đó
			if (aniSet->at(curAniID)->IsFinalFrame())
				currentAni->RenderFrame(aniSet->at(curAniID)->GetLastFrame(), 0, playOpeningCutScene ? 8 : 0);
			else {
				currentAni->Render(0, playOpeningCutScene ? 8 : 0);
				// Lấy mốc thời gian khi render frame đầu tiên
				if (currentAni->GetCurrentFrame() == 0)
					lifeTimeAni = GetTickCount64();
			}

			// Kiểm tra xem đã render ani đủ thời gian yêu cầu chưa
			if (GetTickCount64() - lifeTimeAni > aniSet->at(curAniID)->GetAniTime())
				curAniID++;
		}
		else
		{
			AutoSwitchScene();
		}
	}
	else
	{
		if (curAniID < aniSet->size())
		{

			CSprites::GetInstance()->Get(ID_KHUNG_VIEN)->Draw(0, 0);
			currentAni = aniSet->at(curAniID);
			//Nếu là frame cuối cùng thì chỉ render frame đó
			if (curAniID == 0)
			{
				currentAni->Render(0, 0);

				if (GetTickCount64() - lifeTimeAni > 6000)
					curAniID++;
			}
			else {
				currentAni->Render(0, 0);
				// Chuyển Scene nếu hoàn thành Intro
				if (currentAni->GetIsComplete())
					CGame::GetInstance()->SwitchScene(SCENE_TYPE_OVERWORLD);
			}

		}
	}
	
}

/*
	Unload current scene
*/
void CIntro::Unload()
{
	/*for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	sophia = NULL;
	jason = NULL;
	bigJason = NULL;
	map = NULL;
	camera = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);*/
}

void CIntro::ChangeAniSet()
{
	if (playOpeningCutScene)
	{
		aniSet = CAnimationSets::GetInstance()->Get(SCENE_TYPE_OPENING_CUTSCENE);
	}
	else if (playTitleScene)
	{
		aniSet = CAnimationSets::GetInstance()->Get(SCENE_TYPE_TITLE_SCENE);
	}
	else if (playRollOutScene)
	{
		aniSet = CAnimationSets::GetInstance()->Get(SCENE_TYPE_ROLL_OUT_SCENE);
	}

}

void CIntro::AutoSwitchScene()
{
	if (playTitleScene)
	{
		// Check xem nếu đã chạy Title Scene thứ 2 rồi thì chuyển sang RollOut Scene

		playOpeningCutScene = false;
		playTitleScene = false;
		playRollOutScene = true;
		ChangeAniSet();
	}
	else if (!playOpeningCutScene)
	{
		// Check xem nếu chưa chạy Opening CutScene thì cho chạy
		playOpeningCutScene = true;
		playTitleScene = false;
		playRollOutScene = false;
		ChangeAniSet();
	}
	else if (playOpeningCutScene)
	{
		// Check xem nếu đã chạy Opening CutScene rồi thì chuyển sang Title Scene
		playOpeningCutScene = false;
		playTitleScene = true;
		playRollOutScene = false;
		ChangeAniSet();
		lifeTimeAni = GetTickCount64();
	}
	else
	{
		// Chạy xong RollOut Scene thì chuyển scene sang OverWorld
		Unload();
		CGame::GetInstance()->SwitchScene(SCENE_TYPE_OVERWORLD);
	}
}

void CIntroKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	_KEYCODE[KeyCode] = true;
	switch (KeyCode)
	{
	
	case DIK_NUMPADENTER:
	{
		/// 
		/// Thứ tự chuyển cảnh là: Title->OpeningCut->Title->RollOut
		/// Những câu lệnh if bên dưới là để kiểm tra khi nhấn nút Enter-> nên sẽ bắt đầu 
		///		check phím từ OpeningCut (Không tính lần chạy Title đầu tiên)
		/// 
		if (((CIntro*)scence)->GetPlayTitleScene()) 
		{
			// Check xem nếu đã chạy Title Scene thứ 2 rồi thì chuyển sang RollOut Scene

			((CIntro*)scence)->SetPlayOpeningCutScene(false);
			((CIntro*)scence)->SetPlayTitleScene(false);
			((CIntro*)scence)->SetPlayRollOutScene(true);
			((CIntro*)scence)->ChangeAniSet();
		}
		else if (!((CIntro*)scence)->GetPlayOpeningCutScene())
		{
			// Check xem nếu chưa chạy Opening CutScene thì cho chạy
			((CIntro*)scence)->SetPlayOpeningCutScene(true);
			((CIntro*)scence)->SetPlayTitleScene(false);
			((CIntro*)scence)->SetPlayRollOutScene(false);
			((CIntro*)scence)->ChangeAniSet();
		}
		else if (((CIntro*)scence)->GetPlayOpeningCutScene())
		{
			// Check xem nếu đã chạy Opening CutScene rồi thì chuyển sang Title Scene
			((CIntro*)scence)->SetPlayOpeningCutScene(false);
			((CIntro*)scence)->SetPlayTitleScene(true);
			((CIntro*)scence)->SetPlayRollOutScene(false);
			((CIntro*)scence)->ChangeAniSet();
		}
		else
		{
			// Chạy xong RollOut Scene thì chuyển scene sang OverWorld
			((CIntro*)scence)->Unload();
			CGame::GetInstance()->SwitchScene(SCENE_TYPE_OVERWORLD);
		}
		break;
	}
	}
	
}

void CIntroKeyHandler::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
		_KEYCODE[KeyCode] = false;
		//bigJason->OnKeyUp(KeyCode);
	
}

void CIntroKeyHandler::KeyState(BYTE* states)
{


	// disable control key when Sophia die 
	/*if (sophia->GetState() == SOPHIA_STATE_DIE) return;*/

}