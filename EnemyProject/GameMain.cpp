#include "stdafx.h"
#include "GameMain.h"
#include "Background.h"
#include "Player.h"
#include "Enemy.h"


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

	enemy = new Enemy(device, { 900, 350 });
	enemy->Initialize();

	player->EnemyMemoryLink(enemy);
	enemy->PlayerMemoryLink(player);
}

void GameMain::Destroy()
{
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
	player->Update();
	enemy->Update();
}

void GameMain::Render()
{
	background->Render();
	player->Render();
	enemy->Render();
}