#include "stdafx.h"
#include "GameMain.h"
#include "Background.h"
#include "Player.h"
#include "Enemy.h"
#include "BulletManager.h"


GameMain::GameMain(HINSTANCE hInstance, LPCWSTR className, LPCSTR lpCmdLine, int nCmdShow)
	: DxWindow(hInstance, className, lpCmdLine, nCmdShow)
{
}

GameMain::~GameMain()
{
}

void GameMain::Initialize()
{
	BulletManager::GetInstance()->SetDevice(device);

	background = new Background(device);
	background->Initialize();

	player = new Player(device);
	player->Initialize();

	enemy = new Enemy(device, D3DXVECTOR2(900, 350));
	enemy->Initialize();

	//player->EnemyMemoryLink(enemy);
	enemy->PlayerMemoryLink(player);
}

void GameMain::Destroy()
{
	BulletManager::DeleteInstance();

	background->Destroy();
	SAFE_DELETE(background);

	player->Destroy();
	SAFE_DELETE(player);

	enemy->Destroy();
	SAFE_DELETE(enemy);
}

void GameMain::Update()
{
	background->Update();
	BulletManager::GetInstance()->Update();
	player->Update();
	enemy->Update();
}

void GameMain::Render()
{
	background->Render();
	BulletManager::GetInstance()->Render();
	player->Render();
	enemy->Render();
}