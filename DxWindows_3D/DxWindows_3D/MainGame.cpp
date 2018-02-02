#include "stdafx.h"
#include "MainGame.h"
#include "./Scene/Scene.h"
#include "./Scene/Scene_01.h"
#include "./Scene/Scene_02.h"

MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}

HRESULT MainGame::Init()
{
	D3D::GetInstance();
	FRAME->Init();
	TWEAKBAR->Init();
	CAMERA->GetInstance();

	nowScene = new Scene_02;
	nowScene->Init();


	TWEAKBAR->ChangeDraw();
	return S_OK;
}

void MainGame::Release()
{
	nowScene->Release();

	CAMERA->ReleaseInstance();
	TWEAKBAR->ReleaseInstance();
	FRAME->Release();
	FRAME->ReleaseInstance();
	D3D::ReleaseInstance();
}

void MainGame::Update()
{
	//프레임 업데이트
	FRAME->UpdateTime(60.0f);

	//한프레임 갱신 시간
	double timeDelta = FRAME->GetFrameDeltaSec();
	CAMERA->DefaultControl(timeDelta);
	CAMERA->UpdateMatrix();

	nowScene->Update(timeDelta);
}

void MainGame::Render()
{
	D3D::GetInstance()->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);

	nowScene->Render();

	TWEAKBAR->Render();
	D3D::GetInstance()->EndScene();
}

LRESULT MainGame::MainProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	TWEAKBAR->InputProc(hWnd, msg, wParam, lParam);
	if (msg == WM_CLOSE || msg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
