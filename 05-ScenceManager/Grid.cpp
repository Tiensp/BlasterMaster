#include "Grid.h"


CGrid::CGrid(int map_w, int map_h)
{
	Rows = map_w / CELL_SIZE;
	Columns = map_h / CELL_SIZE;

	Cell = new vector<CGameObject*> * [Rows + 1];
	for (int i = 0; i < Rows + 1; i++)
	{
		Cell[i] = new vector<CGameObject*>[Columns + 1];
	}
}

CGrid::~CGrid()
{
}

void CGrid::AddObject(LPGAMEOBJECT obj)
{
	float left, right, top, bottom;
	obj->GetBoundingBox(left, right, top, bottom);

	int start_col = left / CELL_SIZE;
	int start_row = top / CELL_SIZE;
	int end_col = right / CELL_SIZE;
	int end_row = bottom / CELL_SIZE;

	for (int i = start_row; i <= end_row; i++)
	{
		for (int j = start_col; j <= end_col; j++)
		{
			Cell[i][j].push_back(obj);
		}
	}

}

void CGrid::RemoveObject(LPGAMEOBJECT obj)
{
	float left, right, top, bottom;
	obj->GetBoundingBox(left, right, top, bottom);

	int start_col = left / CELL_SIZE - 2;
	int start_row = top / CELL_SIZE + 2;
	int end_col = right / CELL_SIZE - 2;
	int end_row = bottom / CELL_SIZE + 2;

	for (int i = start_row; i <= end_row; i++)
	{
		for (int j = start_col; j <= end_col; j++)
		{
			for (int index = 0; index < Cell[i][j].size(); index++)
			{
				if (Cell[i][j].at(index) == obj)
				{
					Cell[i][j].erase(Cell[i][j].begin() + index);
				}
			}
		}
	}
}

void CGrid::Update(vector<LPGAMEOBJECT> obj)
{
	for (int i = 0; i < obj.size(); i++) 
	{
		if (!dynamic_cast<CBrick*>(obj.at(i)) && !dynamic_cast<CPortal*>(obj.at(i)))
		{
			RemoveObject(obj.at(i));
			AddObject(obj.at(i));
		}
	}
}

void CGrid::UnloadGrid()
{
	for (int i = 0; i < Rows; i++)
	{
		delete[] Cell[i];
	}

	delete Cell;
}

vector<LPGAMEOBJECT> CGrid::SortDuplicateObj(vector<LPGAMEOBJECT> obj)
{
	sort(obj.begin(), obj.end());
	obj.erase(unique(obj.begin(), obj.end()), obj.end());
	return obj;
}

vector<LPGAMEOBJECT> CGrid::GetActiveObj()
{
	CCamera* camera = CCamera::GetInstance();
	D3DXVECTOR2 camPos = camera->GetCamPos();

	int start_col = camPos.x / CELL_SIZE;
	int start_row = camPos.y / CELL_SIZE;

	int end_col = (camPos.x + camera->GetWidth()) / CELL_SIZE;
	int end_row = (camPos.y + camera->GetHeight()) / CELL_SIZE;
	
	vector<LPGAMEOBJECT> activeObj;
	for (int i = start_row; i <= end_row; i++)
	{
		for (int j = start_col; j <= end_col; j++)
		{
			for (int index = 0; index < Cell[i][j].size(); index++)
			{
				activeObj.push_back(Cell[i][j].at(index));
			}
		}
	}

	activeObj = SortDuplicateObj(activeObj);

	return activeObj;
}
