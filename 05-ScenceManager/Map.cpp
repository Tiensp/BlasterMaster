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
	//Đọc dòng đầu tiên: kích thước tile, số cột tile, số hàng tile, số cột matrix, số hàng matrix
	f >> TileSize >> TileCols >> TileRows >> MapCols >> MapRows;
	//Đọc matrix
	for (int i = 0; i < MapRows; i++)
		for (int j = 0; j < MapCols; j++)
		{
			f >> Matrix[i][j];
		}
	f.close();
}

void CMap::LoadTileSet(string filePath)
{
	//Add Texture TileMap từ path file ảnh (.PNG,...)
	CTextures::GetInstance()->Add(static_cast<ObjectType>(id + MAPID), ToLPCWSTR(filePath), D3DCOLOR_XRGB(255, 255, 255)); 
	TileTexture = CTextures::GetInstance()->Get(static_cast<ObjectType>(id + MAPID));
}


void CMap::DrawMap()
{


	//D3DXVECTOR2 camPos = CCamera::GetInstance()->GetCamPos();
	//DebugOut(L"CamX: %f, CamY: %f\n", camPos.x, camPos.y);
	//for (int i = 0; i < MapRows; i++)
	//	for (int j = 0; j < MapCols; j++)
	//	{
	//		RECT tileRECT;
	//		tileRECT.left = j * 16;
	//		tileRECT.top = i * 16;
	//		tileRECT.right = tileRECT.left + TileSize;
	//		tileRECT.bottom = tileRECT.top + TileSize;

	//		//nếu nằm ngoài Camera thì không render
	//		if (!isContain(tileRECT, CCamera::GetInstance()->GetBoundCam()))
	//			continue;
	//		delete TileSet;
	//		TileSet = new CSprite(static_cast<ObjectType>(MAPID + Matrix[i][j]), tileRECT.left, tileRECT.top, tileRECT.right, tileRECT.bottom, TileTexture);
	//		TileSet->Draw((float)j * 16, (float)i *	16);

	//	}
}
