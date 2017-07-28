#include "stdafx.h"
#include "tankGameScene.h"
#include "TankMap.h"
#include "tank.h"
#include "Scene.h"
tankGameScene::tankGameScene(LPDIRECT3DDEVICE9 device)
	:device(device)
{

}

tankGameScene::~tankGameScene()
{
}

void tankGameScene::Initialize()
{
	
	_tankMap = new TankMap(device);
	_tank = new tank(device);

	(_tank)->setTankMapMemoryLink(_tankMap);
}

void tankGameScene::Destroy()
{
	SAFE_DELETE(_tank);
	SAFE_DELETE(_tankMap);
}

void tankGameScene::Update()
{
	(_tankMap)->update();
	(_tank)->update();
}

void tankGameScene::Render()
{
	(_tankMap)->render();
	(_tank)->render();
}
