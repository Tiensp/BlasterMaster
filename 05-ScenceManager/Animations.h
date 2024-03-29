#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>

#include "Sprites.h"
#include "GameDefine.h"

/*
Sprite animation
*/
class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};

typedef CAnimationFrame *LPANIMATION_FRAME;

class CAnimation
{
	DWORD lastFrameTime;
	int currentFrame;
	int defaultTime;
	vector<LPANIMATION_FRAME>* frames;
	bool isComplete = false;			
public:
	CAnimation(int defaultTime = 100);
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y, int alpha = 255);
	void RenderFrame(int frameID, float x, float y, int alpha = 255);
	void ResetCurrentFrame() { currentFrame = -1; isComplete = false; }
	void SetCurrentFrame(int curr) { currentFrame = curr; }
	int GetCurrentFrame();
	int GetAniSize() { return frames->size(); }
	int GetLastFrame();
	int GetAniTime();
	bool IsFinalFrame();

};

typedef CAnimation *LPANIMATION;

class CAnimations
{
	static CAnimations * __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);
	void Clear();

	static CAnimations * GetInstance();
};

typedef vector<LPANIMATION> CAnimationSet;

typedef CAnimationSet* LPANIMATION_SET;
//class AnimationSet {
//	unordered_map<int, LPANIMATION> animations;
//public:
//	void Add(int aniId, STATENAME StateName);
//	LPANIMATION Get(STATENAME StateName);
//};
//
//typedef AnimationSet* LPANIMATION_SET;

/*
	Manage animation set database
*/
class CAnimationSets
{
	static CAnimationSets * __instance;

	unordered_map<int, LPANIMATION_SET> animation_sets;

public:
	CAnimationSets();
	void Add(int id, LPANIMATION_SET ani);
	LPANIMATION_SET Get(unsigned int id);


	static CAnimationSets * GetInstance();
};