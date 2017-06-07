#include "stdafx.h"
#include "GameMain.h"
#include "DrawCircle.h"
#include "DrawRect.h"
#include "Intersect.h"


GameMain::GameMain(HINSTANCE hInstance, LPCWSTR className, LPCSTR lpCmdLine, int nCmdShow)
	: DxWindow(hInstance, className, lpCmdLine, nCmdShow)
	, prevTime1(0)
{
}


GameMain::~GameMain()
{
}

void GameMain::Initialize()
{
	DrawRect* rect1;
	POINT rCoord = { 0,  600 };
	POINT size = { winSize.x, winSize.y - 600 };
	rect1 = new DrawRect(device, rCoord, size);
	rect1->Initialize();
	
	DrawRect* rect2;
	POINT rCoord1 = { rect1->GetSize().x + 100,  500 };
	POINT size1 = { 500, 600 };
	rect2 = new DrawRect(device, rCoord1, size1);
	rect2->Initialize();

	rectList.push_back(rect1);
	rectList.push_back(rect2);

	POINT cCoord = { 550, 550 };
	float radius = 50.0f;
	circle = new DrawCircle(device, cCoord, radius);
	circle->Initalize();



}

void GameMain::Destroy()
{
	circle->Destroy();
	SAFE_DELETE(circle);
	
	for (int i = 0; i < (int)rectList.size(); i++) {
		rectList[i]->Destroy();
		rectList.clear();
	}


	Keyboard::DeleteInstance();
	Mouse::DeleteInstance();
}

void GameMain::Update()
{


	DWORD curTime2 = timeGetTime();
	if (prevTime2 == 0 || (prevTime2 - curTime2) > 2) {

		for (int i = 0; i < (int)rectList.size(); i++) {

		POINT mCoord = rectList[i]->GetCoord();
		mCoord.x -= 10;
		float width = rectList[i]->GetRect().right - rectList[i]->GetRect().left;
		if (rectList[i]->GetRect().right <= 0)
			mCoord = { winSize.x+ i*100, rectList[i]->GetCoord().y };


		rectList[i]->SetCoord(mCoord);
		}
		prevTime2 = curTime2;
	}

	/*if (Intersect::IsCircleInRect(
		&circle->GetCoord(), circle->GetRadius(),
		&rect->GetRect())) {
		circle->SetColor(0xFFFF0000);
		rect->SetColor(0xFF00FF00);
	}
	else {
		circle->SetColor(0xFF000000);
		rect->SetColor(0xFF000000);
	}*/





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
	for (int i = 0; i < (int)rectList.size(); i++) {
		rectList[i]->Render();
	}

	device->EndScene();
	device->Present(0, 0, 0, 0);
}
