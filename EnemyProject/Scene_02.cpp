#include "stdafx.h"
#include "Scene_02.h"

Scene_02::Scene_02(LPDIRECT3DDEVICE9 device)
	:Scene(device)
{
	Scene::device = device;
	this->Initialize();
}

Scene_02::~Scene_02()
{
}

void Scene_02::Initialize()
{
}

void Scene_02::Destroy()
{
	if (Keyboard::GetInstance()->KeyDown(VK_Q))
		SceneManager::GetInstance()->ChangeScene("Scene01");
}

void Scene_02::Update()
{
}

void Scene_02::Render()
{
}
