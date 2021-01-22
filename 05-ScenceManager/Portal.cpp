#include "Portal.h"



CPortal::CPortal(float _x, float _y, int sceneID, int portalID, int desScene, int _nx, int type, float xDes, float yDes)
{
	scene_id = sceneID;
	portal_id = portalID;
	des_scene = desScene;
	x = _x; 
	y = _y;
	x_des = xDes;
	y_des = yDes;
	nx = _nx;
	objTag = PORTAL;
	objType = static_cast<ObjectTYPE> (type);
	if (objType == OverWorld1 || objType == OverWorld2 || objType == OverWorld3 || objType == OverWorld4)
	{
		/*
			portal_id lẻ là những portal phía bên phải của scene và hướng nx = -1
			portal_id chẵn là những portal phía bên trái của scene và hướng nx = 1
			
			+ Vì khi chuyển Scene nhân vật sẽ di chuyển từ từ vào cổng và chỉ có một phần của cổng
			render đè lên trên xe nên để mô phỏng chân thật nhất, mình sẽ chỉ render 1 phần 
			của cổng.
			+ Xem lại Sprite Portal để hiểu cách tính tọa độ x_render, y_render
		*/
		width = PORTAL_WIDTH;
		height = PORTAL_OVW_HEIGHT;

		if (nx < 0)	
		{
			x_render = x + width / 2;
		}
		else
		{
			x_render = x - 32 ;	//32 là độ dày của tường :D
		}
		
		y_render = y;
	}
	else
	{
		switch (objType)
		{
		case SpecialPortal:
		{
			width = PORTAL_WIDTH;
			height = PORTAL_OVW_HEIGHT;
			x_render = x + width / 2 - 2;
			y_render = y;
			break; 
		}
		case OVHHorizontal:
		{
			width = PORTAL_WIDTH;
			height = PORTAL_OVH_HOR_HEIGHT;
			x_render = x;
			y_render = y - 16;
			break; 
		}
		case OVHVerticle:
		{
			width = PORTAL_WIDTH;
			height = PORTAL_OVH_VER_HEIGHT;
			x_render = x - 16;
			if (nx < 0)
				y_render = y;
			else
				y_render = y - 32;
			break; 
		}
		case ToOverWorld:
		{
			width = PORTAL_ToOVW_SIZE;
			height = PORTAL_ToOVW_SIZE;
			x_render = x;
			y_render = y;
			break;
		}
		}
	}
}

void CPortal::Render()
{
	switch (objType)
	{
	case OverWorld1:
	{
		if (nx > 0)
			animation_set->at(PORTAL_TYPE2)->RenderFrame(0, x_render, y_render);
		else
			animation_set->at(PORTAL_TYPE3)->RenderFrame(0, x_render, y_render);
		break;
	}
	case OverWorld2:
	{
		if (nx > 0)
			animation_set->at(PORTAL_TYPE4)->RenderFrame(0, x_render, y_render);
		else
			animation_set->at(PORTAL_TYPE5)->RenderFrame(0, x_render, y_render);
		break;
	}
	case OverWorld3:
	{
		if (nx > 0)
			animation_set->at(PORTAL_TYPE6)->RenderFrame(0, x_render, y_render);
		else
			animation_set->at(PORTAL_TYPE7)->RenderFrame(0, x_render, y_render);
		break;
	}
	case OverWorld4:
	{
		if (nx > 0)
			animation_set->at(PORTAL_TYPE8)->RenderFrame(0, x_render, y_render);
		else
			animation_set->at(PORTAL_TYPE9)->RenderFrame(0, x_render, y_render);
		break;
	}
	case SpecialPortal:
	{
			animation_set->at(PORTAL_TYPE0)->RenderFrame(0, x_render, y_render);
		break;
	}
	case OVHHorizontal:
	{
		if (nx < 0)
			animation_set->at(PORTAL_TYPE10)->RenderFrame(0, x_render, y_render);
		else
			animation_set->at(PORTAL_TYPE11)->RenderFrame(0, x_render, y_render);
		break;
	}
	case OVHVerticle:
	{
		if (nx < 0)
			animation_set->at(PORTAL_TYPE12)->RenderFrame(0, x_render, y_render);
		else
			animation_set->at(PORTAL_TYPE13)->RenderFrame(0, x_render, y_render);
		break;
	}
	}

	RenderBoundingBox(x, y);
}

void CPortal::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}