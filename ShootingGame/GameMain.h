#pragma once
#include "DxWindow.h"

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
	DrawRect* winRect;
	DrawRect* mainRect;
	DrawRect* wellRect[10];
	DrawRect* monsterRect[4];
	DrawRect* bullet;
	vector <DrawRect*> bulletList;

	DWORD prevTime1;
	DWORD prevTime2;

};

