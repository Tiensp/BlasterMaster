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
	int Matrix[200][200];
public:
	CMap(int id, string fileMatrix, string fileTileSet);
	~CMap();
	void LoadMatrix(string filePath);
	void LoadTileSet(string filePath);
	void DrawMap();
	bool isContain(RECT rect1, RECT rect2);


};

