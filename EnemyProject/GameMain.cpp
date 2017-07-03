#include "stdafx.h"
#include "GameMain.h"
#include "Background.h"
#include "Player.h"
#include "EnemyManager.h"


GameMain::GameMain(HINSTANCE hInstance, LPCWSTR className, LPCSTR lpCmdLine, int nCmdShow)
	: DxWindow(hInstance, className, lpCmdLine, nCmdShow)
{
}

GameMain::~GameMain()
{
}

void GameMain::Initialize()
{
	background = new Background(device);
	background->Initialize();

	player = new Player(device);
	player->Initialize();

	EnemyManager::GetInstance()->SetDevice(device);
}

void GameMain::Destroy()
{
	background->Destroy();
	SAFE_DELETE(background);

	player->Destroy();
	SAFE_DELETE(player);
	
	EnemyManager::DeleteInstance();
}

void GameMain::Update()
{
	background->Update();
	player->Update();
	EnemyManager::GetInstance()->Update();
}

void GameMain::Render()
{
	background->Render();
	player->Render();
	EnemyManager::GetInstance()->Render();
}