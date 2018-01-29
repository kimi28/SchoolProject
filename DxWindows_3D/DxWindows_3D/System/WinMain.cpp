#include "../stdafx.h"
#include "../MainGame.h"

HWND g_hWnd;
HINSTANCE g_hInst;

MainGame g_mainGame;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdParam, int nCmdShow)
{
	g_hInst = hInstance;

	WNDCLASS WndClass;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = WIN_CLASS;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&WndClass);

	g_hWnd = CreateWindow
	(
		WIN_CLASS,
		WIN_TITLE,
		WIN_STYLE,
		WINPOS_X,
		WINPOS_Y,
		WINSIZE_X,
		WINSIZE_Y,
		GetDesktopWindow(),
		NULL,
		hInstance,
		NULL
	);

	RECT rcClient = { 0,0,WINSIZE_X,WINSIZE_Y };

	AdjustWindowRect(&rcClient, WIN_STYLE, FALSE);

	SetWindowPos
	(
		g_hWnd,
		NULL,
		0, 0,
		rcClient.right - rcClient.left,
		rcClient.bottom - rcClient.top,
		SWP_NOZORDER | SWP_NOMOVE
	);

	//메세지 구조체 
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

	//등록되어있는 윈도우 해제인데.......(안해도 상관은 없다)
	UnregisterClass(WIN_CLASS, hInstance);

	//윈도우 프로그램 종료
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return g_mainGame.MainProc(hWnd, msg, wParam, lParam);
}