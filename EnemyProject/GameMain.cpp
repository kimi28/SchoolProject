#include "stdafx.h"
#include "GameMain.h"
#include "Background.h"
#include "Player.h"
#include "Enemy.h"
#include "BulletManager.h"
#include "Animation.h"


GameMain::GameMain(HINSTANCE hInstance, LPCWSTR className, LPCSTR lpCmdLine, int nCmdShow)
	: DxWindow(hInstance, className, lpCmdLine, nCmdShow)
{
}

GameMain::~GameMain()
{
}

void GameMain::Initialize()
{
	SoundManager::GetInstance()->AddSound("배경", "Sounds/Airport.mp3", true, true);
	SoundManager::GetInstance()->Play("배경");

	//animation = new Animation(device, L"Textures/cat.png", { 4,2 }, { 150, 100 });
	//animation->Initialize();

	//frame = { 0,0 };

	//time = timeGetTime();

	background = new Background(device);
	background->Initialize();

	player = new Player(device);
	player->Initialize();

	enemy = new Enemy(device, D3DXVECTOR2(900, 350));
	enemy->Initialize();

	//player->EnemyMemoryLink(enemy);
	//enemy->PlayerMemoryLink(player);
}

void GameMain::Destroy()
{

	//SAFE_DELETE(animation);


	background->Destroy();
	SAFE_DELETE(background);

	player->Destroy();
	SAFE_DELETE(player);

	enemy->Destroy();
	SAFE_DELETE(enemy);
}

void GameMain::Update()
{
	//DWORD currentTime = timeGetTime();
	//if (currentTime - time > 100) {
	//	animation->Update(frame);
	//	frame.x++;
	//	if (frame.x == 3) {
	//		frame.x = 0;
	//		if (frame.y == 0)
	//			frame.y++;
	//		else
	//			frame.y--;
	//	}
	//	time = timeGetTime();
	//}
	background->Update();
	
	player->Update();
	enemy->Update();
}

void GameMain::Render()
{
	//animation->Render();
	background->Render();
	
	player->Render();
	enemy->Render();
}