#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "GameDefine.h"
#include "Grid.h"

class CIntro : public CScene
{
protected:

	
	LPANIMATION_SET aniSet;
	LPANIMATION currentAni;
	
	CCamera* camera;

	DWORD lifeTimeAni;
	bool playTitleScene;
	bool playOpeningCutScene;
	bool playRollOutScene;

	/* Các hàm ParsSection dùng để đọc file */
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);


public:
	CIntro(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	void SetPlayTitleScene(bool _playTitleScene) { this->playTitleScene = _playTitleScene; }
	bool GetPlayTitleScene() { return playTitleScene; }


	void SetPlayOpeningCutScene(bool _playOpeningCutScene) { this->playOpeningCutScene = _playOpeningCutScene; }
	bool GetPlayOpeningCutScene() { return playOpeningCutScene; }

	void SetPlayRollOutScene(bool _playRollOutScene) { this->playRollOutScene = _playRollOutScene; }
	bool GetPlayRollOutScene() { return playRollOutScene; }

	void ChangeAniSet();
	void AutoSwitchScene();

	//////// PUBLIC VARIABLE //////////
	int curAniID = 0;
};

class CIntroKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CIntroKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};

