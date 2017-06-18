#include "stdafx.h"
#include "GameMain.h"
#include "Player.h"


GameMain::GameMain(HINSTANCE hInstance, LPCWSTR className, LPCSTR lpCmdLine, int nCmdShow)
	: DxWindow(hInstance, className, lpCmdLine, nCmdShow)
{
}

GameMain::~GameMain()
{
}

void GameMain::Initialize()
{
	player = new Player(device, { 20, 10 });
}

void GameMain::Destroy()
{
	player->Destroy();
	SAFE_DELETE(player);
}

void GameMain::Update()
{
	player->Update();
}

void GameMain::Render()
{
	player->Render();
}
