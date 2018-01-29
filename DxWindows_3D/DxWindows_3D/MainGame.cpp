#include "stdafx.h"
#include "MainGame.h"



MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}

HRESULT MainGame::Init()
{
	D3D::GetInstance();
	return S_OK;
}

void MainGame::Release()
{
	D3D::ReleaseInstance();
}

void MainGame::Update()
{
}

void MainGame::Render()
{
	D3D::GetInstance()->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);

	D3D::GetInstance()->EndScene();
}

LRESULT MainGame::MainProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//TWEAKBAR->InputProc(hWnd, msg, wParam, lParam);
	if (msg == WM_CLOSE || msg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
