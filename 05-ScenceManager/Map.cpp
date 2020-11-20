#include "Map.h"
#include "Utils.h"
#include <fstream>
#include "Game.h"

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
	DebugOut(L"[INFO] Start loading matrix map: %s\n", ToLPCWSTR(filePath));

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

	DebugOut(L"[INFO] Done loading matrix map\n");
}

void CMap::LoadTileSet(string filePath)
{
	DebugOut(L"[INFO] Start loading tile set map: %s\n", ToLPCWSTR(filePath));
	//Add Texture TileMap từ path file ảnh (.PNG,...)
	CTextures::GetInstance()->Add(static_cast<ObjectType>(id + MAPID), ToLPCWSTR(filePath), D3DCOLOR_XRGB(255, 255, 255)); 
	TileTexture = CTextures::GetInstance()->Get(static_cast<ObjectType>(id + MAPID));
	DebugOut(L"[INFO] Done loading tile set map\n");
}


void CMap::DrawMap()
{
	/*  
		Từ một tọa độ bất kỳ trong Map,
		Ta có thể biết được tọa độ đó nằm trong ô nào của MatrixMap
		Bằng cách chia tọa độ cho kích thước của Tile (TileWidth, TileHeight) 
	*/

	/*		
		Do đó ta sẽ tính xem tọa độ Camera hiện tại đang nằm ở vị trí nào
	    Và bắt đầu fill những tile nằm trong vùng Camera (fill từ start->end) 
	*/
	CCamera* camera = CCamera::GetInstance();
	D3DXVECTOR2 camPos = camera->GetCamPos();
	//DebugOut(L"CamX: %f, CamY: %f\n", camPos.x, camPos.y);
	int start_Col = camPos.x / TileSize;
	int start_Row = camPos.y / TileSize;

	/* 
		Thỉnh thoảng trong lúc tính toán và làm tròn sẽ có ô không được fill
		Vì vậy ta sẽ +2 (hoặc bao nhiêu tùy chọn) để có thể vẽ hết tất cả và không bị flick cạnh 
	*/
	int end_Col = (camera->GetWidth() / TileSize) + start_Col + 2;
	int end_Row = (camera->GetHeight() / TileSize) + start_Row + 2;

	/*
		 Để tìm xem tile nằm ở vị trí nào trong TileSet texture
		 Ta lấy mã tile (chính là thứ tự của tile trong TileSet)
			  - chia lấy dư cho số cột file TileSet để biết tile nằm ở cột nào: id % tileCols
			  - chia lấy phần nguyên cho số cột file TileSet để biết tile nằm ở hàng nào: id/ tileCols
		 Sử dụng biến:
				id_tile: để lưu ID Tile
				m, n: để lưu vị trí cột, hàng của tile
				tileRECT: để lưu tile RECT 
	*/
	int id_tile;
	int m, n;
	RECT tileRECT;
	
	for (int i = start_Col; i <= end_Col; i++)
		for (int j = start_Row; j <= end_Row; j++)
		{
			if (i < 0 || j < 0)
				continue;
			if (i >= MapCols || j >= MapRows)
				continue;
			//Tọa độ của tile trong Map
			D3DXVECTOR2 renderPos(i * TileSize, j * TileSize);

			id_tile = Matrix[j][i];
			m = id_tile % TileCols;
			n = id_tile / TileCols;
			tileRECT.left = m * TileSize;
			tileRECT.top = n * TileSize;
			tileRECT.right = tileRECT.left + TileSize;
			tileRECT.bottom = tileRECT.top + TileSize;

			CGame::GetInstance()->Draw(renderPos, TileTexture, tileRECT);
		}

}
