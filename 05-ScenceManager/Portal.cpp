#include "Portal.h"


CPortal::CPortal(float _x, float _y, int sceneID, int portalID, int _nx, int type, float xDes, float yDes)
{
	scene_id = sceneID;
	portal_id = portalID;
	x = _x; 
	y = _y;
	x_des = xDes;
	y_des = yDes;
	nx = _nx;
	width = PORTAL_HEIGHT;
	height = PORTAL_HEIGHT;
	objTag = Portal;
	objType = static_cast<ObjectTYPE> (type);
	y_render = y;
	if (objType == OverWorld)
	{
		/*
			portal_id lẻ là những portal phía bên phải của scene và hướng nx = -1
			portal_id chẵn là những portal phía bên trái của scene và hướng nx = 1
			
			+ Vì khi chuyển Scene nhân vật sẽ di chuyển từ từ vào cổng và chỉ có một phần của cổng
			render đè lên trên xe nên để mô phỏng chân thật nhất, mình sẽ chỉ render 1 phần 
			của cổng.
			+ Xem lại Sprite Portal để hiểu cách tính tọa độ x_render, y_render
		*/

		if (nx > 0)	
		{
			x_render = x + width / 2;
		}
		else
		{
			x_render = x - 32 ;	//32 là độ dày của tường :D
		}
	}
}

void CPortal::Render()
{
	if (objType == OverWorld)
		animation_set->at(scene_id)->RenderFrame(portal_id, x_render, y_render);
	RenderBoundingBox(x_render, y_render);
}

void CPortal::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}