#include "stdafx.h"
#include "TankGameScene.h"
#include "Scene.h"
#include "TileMap.h"
#include "TileLoad.h"
#include "Tank.h"


TankGameScene::TankGameScene(LPDIRECT3DDEVICE9 device)
	: device(device)
{
	
}


TankGameScene::~TankGameScene()
{
}

void TankGameScene::Initialize()
{
	tileMap = new TileMap(device);
	tank = new Tank(device);

	tank->SetTankMapMemoryLink(tileMap);
}

void TankGameScene::Destroy()
{
	SAFE_DELETE(tileMap);
	SAFE_DELETE(tank);
}

void TankGameScene::Update()
{
	tileMap->Update();
	tank->Update();
}

void TankGameScene::Render()
{
	tileMap->Render();
	tank->Render();
}
