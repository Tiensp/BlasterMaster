#include "Grid.h"
#include "Item.h"
#include "Sophia.h"


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
	float left, top, right, bottom;
	obj->GetBoundingBox(left, top, right, bottom);

	int start_col = left / CELL_SIZE;
	int start_row = top / CELL_SIZE;
	int end_col = right / CELL_SIZE;
	int end_row = bottom / CELL_SIZE;

	for (int i = start_row; i <= end_row; i++)
	{
		for (int j = start_col; j <= end_col; j++)
		{
			DebugOut(L"Cell[%d][%d]", i, j);
			Cell[i][j].push_back(obj);
		}
	}
}

void CGrid::RemoveObject(LPGAMEOBJECT obj)
{
	float left, right, top, bottom;
	obj->GetBoundingBox(left, top, right, bottom);

	int start_col = left / CELL_SIZE - 1;
	int start_row = top / CELL_SIZE - 1;
	int end_col = right / CELL_SIZE + 1;
	int end_row = bottom / CELL_SIZE + 1;
	if (start_col < 0)
		start_col = 0;
	if (end_col > Columns)
		end_col = Columns;
	if (start_row < 0)
		start_row = 0;
	if (end_row > Rows)
		end_row = Rows;

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
		if (!dynamic_cast<CBrick*>(obj.at(i)) && !dynamic_cast<CPortal*>(obj.at(i)) &&
			!dynamic_cast<CItem*>(obj.at(i)) && !dynamic_cast<CLadder*>(obj.at(i)))
		{
			if (dynamic_cast<Enemy*>(obj.at(i)))
			{
				Enemy* e = dynamic_cast<Enemy*>(obj.at(i));
				if (e->GetIsDeath())
					continue;
			}
			/*else if (dynamic_cast<CItem*>(obj.at(i)))
			{
				CItem* e = dynamic_cast<CItem*>(obj.at(i));
				if (e->isDeath)
					continue;
			}*/

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
	CGameObject* obj;
	for (int i = start_row; i <= end_row; i++)
	{
		for (int j = start_col; j <= end_col; j++)
		{
			for (int index = 0; index < Cell[i][j].size(); index++)
			{
				obj = Cell[i][j].at(index);
				if (dynamic_cast<Enemy*>(obj)|| dynamic_cast<CSophia*>(obj) || dynamic_cast<BulletObject*>(obj))
				{
					if (!camera->isContain(D3DXVECTOR2(obj->x, obj->y)))
						continue;
				}
					activeObj.push_back(obj);
			}
		}
	}

	activeObj = SortDuplicateObj(activeObj);

	return activeObj;
}

