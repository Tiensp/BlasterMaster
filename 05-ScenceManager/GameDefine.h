#pragma once
#include <Windows.h>
#include <dinput.h>
#include <WinUser.h> 

#include <stdlib.h> 
#include <stdarg.h> 
#include <stdio.h> 
#include <time.h> 

#include <d3d9.h>
#include <d3dx9.h>

#include "Utils.h"

/*
	Kích thước thật sau khi tạo cửa số sẽ bị giảm đi 
	so với tham số truyền vào vì window phải trừ cho
	borders và title bar. Ở đây mình đo được:
		-15 cho chiều rộng 
		-38 cho chiều cao
*/
#define SCREEN_WIDTH 315
#define SCREEN_HEIGHT 310
#define W_CAM_BOUND 150
enum ObjectType
{
	MAPID = 10000
};
