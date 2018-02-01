#include "stdafx.h"
#include "MainGame.h"
#include "./Render/Model.h"
#include "./Render/Cube.h"
#include "./Render/Star.h"
#include "./Render/ColorShader.h"

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
	colorShader = new ColorShader();
	for (int i = 0; i < 6; i++)
	{
		model[i] = new Cube(colorShader);
	}
	model[0]->GetTransform()->SetWorldPosition(0, 2, 0);
	model[1]->GetTransform()->SetWorldPosition(0, 0, 0);
	model[2]->GetTransform()->SetWorldPosition(-2, 0, 0);
	model[3]->GetTransform()->SetWorldPosition(2, 0, 0);
	model[4]->GetTransform()->SetWorldPosition(1.0f, -2, 0);
	model[5]->GetTransform()->SetWorldPosition(-1.0f, -2, 0);


	TWEAKBAR->ChangeDraw();
	return S_OK;
}

void MainGame::Release()
{
	SAFE_DELETE(colorShader);
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
}

void MainGame::Render()
{
	D3D::GetInstance()->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);

	for (int i = 0; i < 6; i++)
		model[i]->Render();

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
