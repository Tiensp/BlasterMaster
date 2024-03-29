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

	int GetMapWidth() { return MapCols * TileSize; }
	int GetMapHeight() { return MapRows * TileSize; }

};

