#include "stdafx.h"
#include "Scene_02.h"

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
	D3DXCreateLine(device, &line);

	posY = 0;
}

void Scene_02::Destroy()
{
	SAFE_RELEASE(line);
}

void Scene_02::Update()
{
	GetLocalTime(&time);

	for (int i = 0; i < 360; i++) {
		posY = 300.0f - sin(i*PI / 180) * 100;
		lineVector[i] = { 50.0f + i, posY, 0.0f };
	}

	if (Keyboard::GetInstance()->KeyDown(VK_Q))
		SceneManager::GetInstance()->ChangeScene("Scene01");
}

void Scene_02::Render()
{
	D3DVIEWPORT9 viewport;
	device->GetViewport(&viewport);

	D3DXMATRIX ortho;
	D3DXMatrixOrthoOffCenterLH(&ortho, 0, viewport.Width, viewport.Height, 0, 0, 1);

	line->Begin();
	line->DrawTransform(lineVector, 360, &ortho, 0xFFFF0000);
	line->End();

	WCHAR str[255];
	wsprintf(str, L"%d½Ã %dºÐ %dÃÊ", time.wHour, time.wMinute, time.wSecond);
	PrintText::GetInstance()->AddText(str);
}
