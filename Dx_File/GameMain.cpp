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
//���� �ʱ�ȭ
void GameMain::Initialize()
{
	
}
//���� ����
void GameMain::Destroy()
{
	

	Keyboard::GetInstance()->DeleteInstance();
}
//�� ������ ���� ������ ����
void GameMain::Update()
{
	
	Keyboard::GetInstance()->Update();
}
//�� ������ ���� ������
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