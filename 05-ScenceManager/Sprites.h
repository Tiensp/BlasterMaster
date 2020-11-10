#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "Camera.h"
using namespace std;

class CSprite
{
	int id;				// Sprite ID in the sprite database

	int left; 
	int top;
	int right;
	int bottom;

	LPDIRECT3DTEXTURE9 texture;
public: 
	CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);

	void Draw(float x, float y, int alpha = 255, int R = 255, int G = 255, int B = 255);
	void DrawFrame(int _x, int _y, RECT rect, int alpha = 255, int R = 255, int G = 255, int B = 255);

	RECT GetRECT();
};

typedef CSprite * LPSPRITE;

/*
	Manage sprite database
*/
class CSprites
{
	static CSprites * __instance;

	unordered_map<int, LPSPRITE> sprites;

public:
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(int id);
	void CSprites::Clear();

	static CSprites * GetInstance();
};



