#pragma once
#include "GameObject.h"
#include "GameDefine.h"
class CItem : public CGameObject
{
	int ItemType;
	bool isVanish;
public:
	CItem(int type);
	~CItem();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int GetType() { return this->ItemType; }
	void SetIsVanish() { this->isVanish = true; }
	bool GetIsVanish() { return isVanish; }
	void Render();
};

