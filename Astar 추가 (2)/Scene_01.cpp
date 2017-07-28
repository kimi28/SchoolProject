#include "stdafx.h"
#include "Scene_01.h"
#include "Player.h"


Scene_01::Scene_01(LPDIRECT3DDEVICE9 device)
{
	Scene::device = device;
	this->Initialize();
}


Scene_01::~Scene_01()
{
}

void Scene_01::Initialize()
{
	player = new Player(device);
	player->Initialize();

	
}

void Scene_01::Update()
{
	player->Update();

	if (Keyboard::GetInstance()->KeyDown(VK_Q))
	{
		SceneManager::GetInstance()->changeScene("scene2");
	}

}

void Scene_01::Destroy()
{
	
	player->Destroy();
}

void Scene_01::Render()
{
	player->Render();
}
