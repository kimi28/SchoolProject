#pragma once
#include "DxWindow.h"

class DrawCircle;
class DrawRect;
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
	DrawCircle* circle;
	DrawRect* rect;

};

