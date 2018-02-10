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
	return S_OK;
}

void MainGame::Release()
{
}

void MainGame::Update()
{
}

void MainGame::Render()
{
	
}

LRESULT MainGame::MainProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_CLOSE || msg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
