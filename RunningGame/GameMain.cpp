#include "stdafx.h"
#include "GameMain.h"
#include "DrawCircle.h"
#include "DrawRect.h"
#include "Intersect.h"


GameMain::GameMain(HINSTANCE hInstance, LPCWSTR className, LPCSTR lpCmdLine, int nCmdShow)
	: DxWindow(hInstance, className, lpCmdLine, nCmdShow)
{
}


GameMain::~GameMain()
{
}

void GameMain::Initialize()
{
	POINT rCoord = { 0,  600 };
	POINT size = { winSize.x, winSize.y };
	rect = new DrawRect(device, rCoord, size);
	rect->Initialize();

	POINT cCoord = { 550, 550 };
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
	if (Intersect::IsCircleInRect(
		&circle->GetCoord(), circle->GetRadius(),
		&rect->GetRect())) {
		circle->SetColor(0xFFFF0000);
		rect->SetColor(0xFF00FF00);
	}
	else {
		circle->SetColor(0xFF000000);
		rect->SetColor(0xFF000000);
	}





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
