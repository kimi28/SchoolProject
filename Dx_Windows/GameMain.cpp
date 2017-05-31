#include "stdafx.h"
#include "GameMain.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "TestMouse.h"

GameMain::GameMain(HINSTANCE hInstance, LPCWSTR className, LPCSTR lpCmdLine, int nCmdShow)
	: DxWindow(hInstance, className, lpCmdLine, nCmdShow)
{
}


GameMain::~GameMain()
{
}

void GameMain::Initialize()
{
	testMouse = new TestMouse(device);
}

void GameMain::Destroy()
{
	SAFE_DELETE(testMouse);

	Keyboard::DeleteInstance();
	Mouse::DeleteInstance();
}

void GameMain::Update()
{
	Keyboard::GetInstance()->Update();
	Mouse::GetInstance()->Update();
}

void GameMain::Render()
{
	if (device == NULL)
		return;

	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 120, 160), 1.0f, 0);

	device->BeginScene();

	testMouse->Render();

	device->EndScene();
	device->Present(0, 0, 0, 0);
}
