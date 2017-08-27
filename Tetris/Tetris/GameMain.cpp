#include "stdafx.h"
#include "GameMain.h"
#include "Rect.h"
#include "Map.h"


GameMain::GameMain(HINSTANCE hInstance, LPCWSTR className, LPCSTR lpCmdLine, int nCmdShow)
	: DxWindow(hInstance, className, lpCmdLine, nCmdShow)
{
}


GameMain::~GameMain()
{
}

void GameMain::Initialize()
{
	rect = new Rect(device, { 100,100 }, { 300, 600 });
	rect->Initialize();

	map = new Map(device);
	map->Initialize();
}

void GameMain::Destroy()
{
	rect->Destroy();
	SAFE_DELETE(rect);
	map->Destroy();
	SAFE_DELETE(map);
}

void GameMain::Update()
{
	rect->Update();
	map->Update();
}

void GameMain::Render()
{
	rect->Render();
	map->Render();
}
