#include "Map.h"
#include "Utils.h"
#include <fstream>

CMap::CMap(int id, string fileMatrix, string fileTileSet)
{
	this->id = id;
	LoadMatrix(fileMatrix);
	LoadTileSet(fileTileSet);
}

CMap::~CMap()
{
}

void CMap::LoadMatrix(string filePath)
{
	ifstream f(filePath, ios::in);
	//Đọc hàng đầu tiên: kích thước tile, số cột, số dòng Matrix
	f >> TileSize >> TileCols >> TileRows >> MapCols >> MapRows;
	//Đọc matrix
	for (int i = 0; i <MapRows; i++) {
		Matrix[i] = new int[MapCols];
	}
	for (int i = 0; i < MapRows; i++)
		for (int j = 0; j < MapCols; j++)
			f >> Matrix[i][j];
	f.close();
}

void CMap::LoadTileSet(string filePath)
{
	
	CTextures::GetInstance()->Add(static_cast<ObjectType>(id + MAPID), ToLPCWSTR(filePath), D3DCOLOR_XRGB(255, 255, 255));
	TileTexture = CTextures::GetInstance()->Get(static_cast<ObjectType>(id + MAPID));

}

void CMap::DrawMap()
{
	CCamera* camera = CCamera::GetInstance();


}
