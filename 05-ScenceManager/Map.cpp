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
	for (int i = 0; i < MapRows; i++)
		for (int j = 0; j < MapCols; j++)
		{
			f >> Matrix[i][j];
		}
	f.close();
}

void CMap::LoadTileSet(string filePath)
{
	
	CTextures::GetInstance()->Add(static_cast<ObjectType>(id + MAPID), ToLPCWSTR(filePath), D3DCOLOR_XRGB(255, 255, 255));
	TileTexture = CTextures::GetInstance()->Get(static_cast<ObjectType>(id + MAPID));
	DebugOut(L"00");
}

void CMap::DrawMap()
{
	RECT rectCam;
	rectCam.left = 0;
	rectCam.top = 0;
	rectCam.right = rectCam.left + SCREEN_WIDTH;
	rectCam.bottom = rectCam.top + SCREEN_HEIGHT;

	RECT rectTileMapforCam;
	rectTileMapforCam.left = (int)(rectCam.left / 16);
	rectTileMapforCam.top = (int)(rectCam.top / 16);
	rectTileMapforCam.right = (1 + (int)(rectCam.right / 16));
	rectTileMapforCam.bottom = (1 + (int)(rectCam.bottom / 16));

	RECT rect;
	int frame;
	int m, n;

	for (int i = rectTileMapforCam.left; i <= rectTileMapforCam.right; i++)
	{
		for (int j = rectTileMapforCam.top; j <= rectTileMapforCam.bottom; j++)
		{
			if (i < 0 || j < 0)
				continue;
			if (i >= MapCols || j >= MapRows)
				continue;
			D3DXVECTOR3 pos(i * 16, j * 16, 0);
			frame = Matrix[j][i];
			m = frame % TileCols;
			n = frame / TileCols;
			rect.left = 16 * m;
			rect.top = 16 * n;
			rect.right = rect.left + 16;
			rect.bottom = rect.top + 16;

			delete TileSet;
			TileSet = new CSprite(Matrix[i][j], rect.left, rect.top, rect.right, rect.bottom, TileTexture);
			TileSet->Draw(pos.x, pos.y);
		}
	}


}
