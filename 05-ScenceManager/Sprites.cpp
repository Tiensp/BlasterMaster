#include "Sprites.h"
#include "Game.h"
#include "Utils.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}

CSprites * CSprites::__instance = NULL;

CSprites *CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::Draw(float x, float y, int alpha, int R, int G, int B)
{
	CGame * game = CGame::GetInstance();
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;
	//game->GetSpriteHandler()->Draw(texture, r, )

	//D3DXVECTOR2 pos = CCamera::GetInstance()->World2Render(D3DXVECTOR2(x,y));



	game->Draw(x, y, texture, left, top, right, bottom, alpha);
}

void CSprite::DrawFrame(int _x, int _y, RECT rect, int alpha, int R, int G, int B)
{
	CGame* game = CGame::GetInstance();
	D3DXVECTOR2 pos = CCamera::GetInstance()->Transform( D3DXVECTOR2(_x,_y));
	game->GetSpriteHandler()->Draw(texture, &rect, NULL, &D3DXVECTOR3(pos.x, pos.y, 0), D3DCOLOR_ARGB(alpha, R, G, B));
}

RECT CSprite::GetRECT()
{
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;
	return RECT();
}

void CSprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex);
	sprites[id] = s;

	DebugOut(L"[INFO] sprite added: %d, %d, %d, %d, %d \n", id, left, top, right, bottom);
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}

/*
	Clear all loaded textures
*/
void CSprites::Clear()
{
	for (auto x : sprites)
	{
		LPSPRITE s = x.second;
		delete s;
	}

	sprites.clear();
}



