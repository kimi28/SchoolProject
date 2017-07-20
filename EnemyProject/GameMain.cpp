#include "stdafx.h"
#include "TileLoad.h"
#include "GameMain.h"
#include "TankGameScene.h"


GameMain::GameMain(HINSTANCE hInstance, LPCWSTR className, LPCSTR lpCmdLine, int nCmdShow)
	: DxWindow(hInstance, className, lpCmdLine, nCmdShow)
{
}

GameMain::~GameMain()
{
}

void GameMain::Initialize()
{
	SceneManager::GetInstance()->AddScene("Scene_01", new TankGameScene(device));
	SceneManager::GetInstance()->ChangeScene("Scene_01");
}

void GameMain::Destroy()
{
	SceneManager::GetInstance()->Destroy();
	
}

void GameMain::Update()
{
	SceneManager::GetInstance()->Update();
}

void GameMain::Render()
{
	SceneManager::GetInstance()->Render();
	
}