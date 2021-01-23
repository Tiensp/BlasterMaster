#pragma once
#include <algorithm>
#include "GameObject.h"
#include "Map.h"
#include "Camera.h"
#include "Brick.h"
#include "Portal.h"
#include "Enemy.h"
#include "Item.h"
#include "Ladder.h"


using namespace std;

#define CELL_SIZE 128

class CGrid
{
	vector<LPGAMEOBJECT>** Cell;
	
	int Rows;
	int Columns;
public:

	CGrid(int map_w, int map_h);
	~CGrid();
	void AddObject(LPGAMEOBJECT obj);
	void RemoveObject(LPGAMEOBJECT obj);
	void Update(vector<LPGAMEOBJECT> obj);
	void UnloadGrid();
	vector<LPGAMEOBJECT> SortDuplicateObj(vector<LPGAMEOBJECT> obj);

	vector<LPGAMEOBJECT> GetActiveObj();

};

