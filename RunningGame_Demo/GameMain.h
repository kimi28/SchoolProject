#pragma once
#include "DxWindow.h"

class Circle;
class Rect;
class Sprite;

class GameMain : public DxWindow
{
public:
	GameMain(HINSTANCE hInstance, LPCWSTR className, LPCSTR lpCmdLine, int nCmdShow);
	~GameMain();

	void Initialize();
	void Destroy();
	void Update();
	void Render();
	
private:
	Rect* rect;
	Rect* rect1;
	vector<Rect*> vecRect;


};

