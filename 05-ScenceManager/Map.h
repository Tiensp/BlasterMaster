#pragma once
#include "Sprites.h"
#include "Textures.h"
#include "Camera.h"
#include "GameDefine.h"

class CMap
{
private:
	int id;
	LPDIRECT3DTEXTURE9 TileTexture;
	LPSPRITE TileSet;

	int TileCols, TileRows;
	int MapCols, MapRows;
	int TileSize;
	int **Matrix;
public:
	CMap(int id, string fileMatrix , string fileTileSet);
	~CMap();
	void LoadMatrix(string filePath);
	void LoadTileSet(string filePath);
	void DrawMap();
	void DrawMapTransform(float xTrans, float yTrans, int directTrans);
	int GetMapWidth() { return MapCols * TileSize; }
	int GetMapHeight() { return MapRows * TileSize; }
	int GetTileSize() { return TileSize; }

	void SetSpriteTex(CSprite* s, LPDIRECT3DTEXTURE9 texture);
	void SetBoundaryLeftRight(int floor);
};

