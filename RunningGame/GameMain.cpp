#include "stdafx.h"
#include "GameMain.h"
#include "DrawCircle.h"
#include "DrawRect.h"


GameMain::GameMain(HINSTANCE hInstance, LPCWSTR className, LPCSTR lpCmdLine, int nCmdShow)
	: DxWindow(hInstance, className, lpCmdLine, nCmdShow)
{
}


GameMain::~GameMain()
{
}

void GameMain::Initialize()
{
	POINT rCoord = { 200, 200 };
	POINT size = { 100, 100 };
	rect = new DrawRect(device, rCoord, size);
	rect->Initialize();

	POINT cCoord = { 600, 600 };
	float radius = 50.0f;
	circle = new DrawCircle(device, cCoord, radius);
	circle->Initalize();
}

void GameMain::Destroy()
{
	rect->Destroy();
	SAFE_DELETE(rect);
	circle->Destroy();
	SAFE_DELETE(circle);

	Keyboard::DeleteInstance();
	Mouse::DeleteInstance();
}

void GameMain::Update()
{
	POINT moveCoord = circle->GetCoord();
	if (Keyboard::GetInstance()->KeyPress(VK_UP)) {
		moveCoord.y -= 20;
	}
	else if (Keyboard::GetInstance()->KeyPress(VK_DOWN)) {
		moveCoord.y += 20;
	}

	if (Keyboard::GetInstance()->KeyPress(VK_LEFT)) {
		moveCoord.x -= 20;
	}
	else if (Keyboard::GetInstance()->KeyPress(VK_RIGHT)) {
		moveCoord.x += 20;
	}

	circle->SetCoord(moveCoord);

	Keyboard::GetInstance()->Update();
	Mouse::GetInstance()->Update();
}

void GameMain::Render()
{
	if (device == NULL)
		return;

	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(1, 1, 1, 1), 1.0f, 0);

	device->BeginScene();

	circle->Render();
	rect->Render();

	device->EndScene();
	device->Present(0, 0, 0, 0);
}
