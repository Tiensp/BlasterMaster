#pragma once
class MiniScene
{
public:
	MiniScene(int _id, float _x, float _y, int w, int h) { id = _id; x = _x; y = _y; width = w; height = h; }
	~MiniScene() {};
	/* Variable */
	int id;
	float x;
	float y;
	int width;
	int height;
	 
};

