#include "Animations.h"
#include "Utils.h"

CAnimationSets * CAnimationSets::__instance = NULL;

CAnimation::CAnimation(int defaultTime)
{
	this->defaultTime = defaultTime;
	lastFrameTime = -1;
	currentFrame = -1;
	frames = new vector<LPANIMATION_FRAME>();
}

void CAnimation::Add(int spriteId, DWORD time) /* Them ani moi */
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);

	if (sprite == NULL)
	{
		DebugOut(L"[ERROR] Sprite ID %d cannot be found!\n", spriteId);
	}

	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames->push_back(frame);
}

// NOTE: sometimes Animation object is NULL ??? HOW ??? 
void CAnimation::Render(float x, float y, int alpha)
{
	DWORD now = GetTickCount64();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames->at(currentFrame)->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			isComplete = (currentFrame == frames->size() - 1);		/* Da render den frame cuoi cua ani */
			if (currentFrame == frames->size()) currentFrame = 0;
		}
	}

	frames->at(currentFrame)->GetSprite()->Draw(x, y, alpha);
}

void CAnimation::Render(float x, float y, D3DCOLOR color)
{
	DWORD now = GetTickCount64();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames->at(currentFrame)->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			isComplete = (currentFrame == frames->size() - 1);		/* Da render den frame cuoi cua ani */
			if (currentFrame == frames->size()) currentFrame = 0;
		}
	}

	frames->at(currentFrame)->GetSprite()->Draw(x, y, color);
}

void CAnimation::RenderFrame(int frameID, float x, float y, int alpha) /* Render mot ani_frame theo id */
{
	if (frameID == -1 || frameID >= frames->size())
		frameID = 0;
	frames->at(frameID)->GetSprite()->Draw(x, y, alpha);
}

void CAnimation::RenderFrame(int frameID, float x, float y, D3DCOLOR color)
{
	if (frameID == -1 || frameID >= frames->size())
		frameID = 0;
	frames->at(frameID)->GetSprite()->Draw(x, y, color);
}

void CAnimation::RenderThreeBullet(float x, float y, int alpha)
{
	DWORD now = GetTickCount64();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames->at(currentFrame)->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			isComplete = (currentFrame == frames->size() - 1);		/* Da render den frame cuoi cua ani */
			if (currentFrame == frames->size()) currentFrame = 0;
		}
	}
	if (currentFrame == 0)
	{
		frames->at(currentFrame)->GetSprite()->Draw(x, y, alpha);
	}
	else if (currentFrame == 1)
	{
		frames->at(currentFrame-1)->GetSprite()->Draw(x, y, alpha);
		frames->at(currentFrame)->GetSprite()->Draw(x, y + 16, alpha);
	}
	else if (currentFrame == 2)
	{
		frames->at(currentFrame-2)->GetSprite()->Draw(x, y, alpha);
		frames->at(currentFrame-1)->GetSprite()->Draw(x, y + 16, alpha);
		frames->at(currentFrame)->GetSprite()->Draw(x, y+16*2, alpha);
	}
	else if (currentFrame == 3)
	{
		frames->at(currentFrame-3)->GetSprite()->Draw(x, y, alpha);
		frames->at(currentFrame-2)->GetSprite()->Draw(x, y + 16, alpha);
		frames->at(currentFrame-1)->GetSprite()->Draw(x, y + 16 * 2, alpha);
		frames->at(currentFrame)->GetSprite()->Draw(x, y + 16*3, alpha);
	}
	else if (currentFrame == 4)
	{
		frames->at(currentFrame-3)->GetSprite()->Draw(x, y + 16, alpha);
		frames->at(currentFrame-2)->GetSprite()->Draw(x, y + 16 * 2, alpha);
		frames->at(currentFrame-1)->GetSprite()->Draw(x, y + 16 * 3, alpha);
		frames->at(currentFrame)->GetSprite()->Draw(x, y + 16 * 4, alpha);
	}
	else if (currentFrame == 5)
	{
		frames->at(currentFrame-3)->GetSprite()->Draw(x, y + 16 * 2, alpha);
		frames->at(currentFrame-2)->GetSprite()->Draw(x, y + 16 * 3, alpha);
		frames->at(currentFrame-1)->GetSprite()->Draw(x, y + 16 * 4, alpha);
		frames->at(currentFrame)->GetSprite()->Draw(x, y + 16 * 5, alpha);
	}
	/*frames->at(currentFrame)->GetSprite()->Draw(x, y, alpha);*/
}

int CAnimation::GetCurrentFrame()
{
	return currentFrame;
}

int CAnimation::GetLastFrame()	/* Get the last frame of ani */
{
	return frames->size() - 1;
}

int CAnimation::GetFrameTime(int frameID)
{
	return frames->at(frameID)->GetTime();
}

int CAnimation::GetAniTime()
{
	int Sum = 0;
	for (int i = 0; i < frames->size(); i++)
		Sum += frames->at(i)->GetTime();
	return Sum;
}

bool CAnimation::IsFinalFrame()
{
	return currentFrame == frames->size() - 1;
}

RECT CAnimation::GetFrameRect(int id)
{
	RECT r = frames->at(id)->GetSprite()->GetRECT();
	return r;
}

CAnimations * CAnimations::__instance = NULL;

CAnimations * CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION CAnimations::Get(int id)
{
	LPANIMATION ani = animations[id];
	if (ani == NULL)
		DebugOut(L"[ERROR] Failed to find animation id: %d\n", id);
	return ani;
}

void CAnimations::Clear()
{
	for (auto x : animations)
	{
		LPANIMATION ani = x.second;
		delete ani;
	}

	animations.clear();
}

CAnimationSets::CAnimationSets()
{

}

CAnimationSets *CAnimationSets::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimationSets();
	return __instance;
}

LPANIMATION_SET CAnimationSets::Get(unsigned int id)
{
	LPANIMATION_SET ani_set = animation_sets[id];
	if (ani_set == NULL)
		DebugOut(L"[ERROR] Failed to find animation set id: %d\n",id);
	 
	return ani_set;
}

void CAnimationSets::Add(int id, LPANIMATION_SET ani_set)
{
	animation_sets[id] = ani_set;
}

//void AnimationSet::Add(int aniId, STATENAME StateName)
//{
//
//}
//
//LPANIMATION AnimationSet::Get(STATENAME StateName)
//{
//	return LPANIMATION();
//}
