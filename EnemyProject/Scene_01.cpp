#include "stdafx.h"
#include "Scene_01.h"
#include "Scene.h"


Scene_01::Scene_01(LPDIRECT3DDEVICE9 device)
	: Scene(device)
{
	Scene::device = device;
	this->Initialize();
}


Scene_01::~Scene_01()
{
}

void Scene_01::Initialize()
{
	D3DXCreateLine(device, &line);

	posY = 0;
}

void Scene_01::Destroy()
{
	SAFE_RELEASE(line);
}

void Scene_01::Update()
{
	GetLocalTime(&time);

	for (int i = 0; i < 360; i++) {
		posY = 300.0f - tan(i*PI / 180) * 100;
		lineVector[i] = { 50.0f + i, posY, 0.0f };
	}

	if (Keyboard::GetInstance()->KeyDown(VK_Q))
		SceneManager::GetInstance()->ChangeScene("Scene02");
}

void Scene_01::Render()
{
	D3DVIEWPORT9 viewport;
	device->GetViewport(&viewport);

	D3DXMATRIX ortho;
	D3DXMatrixOrthoOffCenterLH(&ortho, 0, viewport.Width, viewport.Height, 0, 0, 1);

	line->Begin();
	line->DrawTransform(lineVector, 360, &ortho, 0xFF0000FF);
	line->End();

	WCHAR str[255];
	wsprintf(str, L"%d½Ã %dºÐ %dÃÊ", time.wHour, time.wMinute, time.wSecond);
	PrintText::GetInstance()->AddText(str);
}
