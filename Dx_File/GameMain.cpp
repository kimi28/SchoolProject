#include "stdafx.h"
#include "GameMain.h"
#include "Keyboard.h"


GameMain::GameMain(HINSTANCE hInstanece, LPCWSTR className, LPCSTR lpCmdLine, int nCmdShow)
	: DxWindow(hInstanece, className, lpCmdLine, nCmdShow)
{
}

GameMain::~GameMain()
{
}
//게임 초기화
void GameMain::Initialize()
{
	
}
//게임 종료
void GameMain::Destroy()
{
	

	Keyboard::GetInstance()->DeleteInstance();
}
//매 프레임 마다 데이터 갱신
void GameMain::Update()
{
	
	Keyboard::GetInstance()->Update();
}
//매 프레임 마다 렌더링
void GameMain::Render()
{
	if (device == NULL) {
		return;
	}

	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 120, 160), 1.0f, 0);
	device->BeginScene();

	

	device->EndScene();
	device->Present(0, 0, 0, 0);
}