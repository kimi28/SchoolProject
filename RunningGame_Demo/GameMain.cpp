#include "stdafx.h"
#include "GameMain.h"
#include "Circle.h"
#include "Rect.h"
#include "Sprite.h"


GameMain::GameMain(HINSTANCE hInstance, LPCWSTR className, LPCSTR lpCmdLine, int nCmdShow)
	: DxWindow(hInstance, className, lpCmdLine, nCmdShow)
{
}


GameMain::~GameMain()
{
}

void GameMain::Initialize()
{
	for (int i = 0; i < vecRect.size(); i += 2) {
		rect = new Rect(device, { 0, 550 }, { 1024, 218 });
		rect->Initialize();
	}
	vecRect.push_back(rect);
}

void GameMain::Destroy()
{
	rect->Destroy();
	SAFE_DELETE(rect);
}

void GameMain::Update()
{
	//vecRect.push_back(rect);
	for (int i = 0; i < vecRect.size(); i++) {
		POINT coord = vecRect[i]->GetCoord();

		coord.x -= 3;

		vecRect[i]->SetCoord(coord);
	}
}

void GameMain::Render()
{
	for (int i = 0; i < vecRect.size(); i+=2) {
		vecRect[i]->Render();
	}
}
