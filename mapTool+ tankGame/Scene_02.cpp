#include "stdafx.h"
#include "Scene.h"
#include "Scene_02.h"
#include "Animation.h"


Scene_02::Scene_02(LPDIRECT3DDEVICE9 device)
{

	Scene::device = device;
	this->Initialize();

}


Scene_02::~Scene_02()
{
}

void Scene_02::Initialize()
{

	animation = new Animation(device, L"Textures/cat.png", { 4,2 }, { 150,100 });
	//animation->Initialize();

	frame = { 0,0 };

	time = timeGetTime();
}

void Scene_02::Update()
{


	DWORD currentTime = timeGetTime();
	if (currentTime - time > 100)
	{
		animation->Update(frame);
		frame.x++;
		if (frame.x == 4)
		{
			frame.x = 0;
			if (frame.y == 0)
				frame.y++;
			else
				frame.y--;
		}


		time = timeGetTime();

	}

	if (Keyboard::GetInstance()->KeyDown(VK_Q))
	{
		SceneManager::GetInstance()->changeScene("scene1");
	}
}

void Scene_02::Destroy()
{

	SAFE_DELETE(animation);

}

void Scene_02::Render()
{

	animation->Render();

}
