#include "stdafx.h"
#include "MainGame.h"
#include "./Render/Model.h"
#include "./Render/Cube.h"
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
	model = new Cube(colorShader);

	TWEAKBAR->ChangeDraw();
	return S_OK;
}

void MainGame::Release()
{
	SAFE_DELETE(model);
	SAFE_DELETE(colorShader);
	CAMERA->ReleaseInstance();
	TWEAKBAR->ReleaseInstance();
	FRAME->Release();
	FRAME->ReleaseInstance();
	D3D::ReleaseInstance();
}

void MainGame::Update()
{
	FRAME->UpdateTime(60.0f);

	double timeDelta = FRAME->GetFrameDeltaSec();

	//model->Update(timeDelta);
	CAMERA->DefaultControl(timeDelta);
	CAMERA->Updatematrix();
}

void MainGame::Render()
{
	D3D::GetInstance()->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);

	model->Render();

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
