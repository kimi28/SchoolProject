#include "../stdafx.h"
#include "../MainGame.h"

HWND		g_hWnd;
HINSTANCE	g_hInst;

MainGame	g_mainGame;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdParam, int nCmdShow)
{
	g_hInst = hInstance;

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = L"DxWindow";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);

	g_hWnd = CreateWindow
	(
		WIN_CLASS
		, WIN_TITLE
		, WIN_STYLE
		, WINPOS_X
		, WINPOS_Y
		, WINSIZE_X
		, WINSIZE_Y
		, GetDesktopWindow()
		, NULL
		, hInstance
		, NULL
	);

	RECT rcClient = { 0, 0, WINSIZE_X, WINSIZE_Y };

	AdjustWindowRect(&rcClient, WIN_STYLE, FALSE);

	SetWindowPos
	(
		g_hWnd
		, NULL
		, 0
		, 0
		, rcClient.right - rcClient.left
		, rcClient.bottom - rcClient.top
		, SWP_NOZORDER | SWP_NOMOVE
	);

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	assert(SUCCEEDED(g_mainGame.Init()));
	
	ShowWindow(g_hWnd, nCmdShow);

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		g_mainGame.Update();

		g_mainGame.Render();

	}

	g_mainGame.Release();

	UnregisterClass(WIN_CLASS, hInstance);

	return	(int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return g_mainGame.MainProc(hWnd, message, wParam, lParam);
}
