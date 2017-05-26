#include "stdafx.h"// 미리컴파일 해더는 항상 최상단에 입력.
#include "DxWindow.h"
#include "GameMain.h"

DxWindow* DxWindow::dxWindow = NULL;

LRESULT CALLBACK wndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return DxWindow::GetDxWindow()->MessageLoop(hwnd, uMsg, wParam, lParam);
}

DxWindow::DxWindow(HINSTANCE hInstance, LPCWSTR lpClassName, LPCSTR lpCmdLine, int nCmdShow)
{
	//lpCmdLine 옵션을 주는 값이 들어 온다.
	dxWindow = this;

	commandShow = nCmdShow;
	instance = hInstance;
	handle = NULL;

	if (lpClassName != NULL) {
		int length = wcslen(lpClassName) + 1;

		className = new WCHAR[length];
		wcscpy_s(className, length, lpClassName);
	}
	else {
		className = NULL;
	}

	if (lpCmdLine != NULL) {
		int length = strlen(lpCmdLine) + 1;

		commandLine = new CHAR[length];
		strcpy_s(commandLine, length, lpCmdLine);
	}
	else {
		commandLine = NULL;
	}

}

DxWindow::~DxWindow()
{
	SAFE_RELEASE(device);
	SAFE_RELEASE(d3d);

	if (handle != NULL)
		DestroyWindow(handle);

	SAFE_DELETE_ARRAY(className);
	SAFE_DELETE_ARRAY(commandLine);
}

void DxWindow::Create(LPCWSTR title)
{
	WNDCLASS wndClass;

	wndClass.cbClsExtra = NULL;
	wndClass.cbWndExtra = NULL;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = instance;
	wndClass.lpfnWndProc = wndProc;
	wndClass.lpszClassName = className;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;

	//	WORD result = RegisterClass(&wndClass);
	//	assert(result == TRUE);

	ATOM result = RegisterClass(&wndClass);
	assert(result != 0);

	RECT rect;
	SetRect(&rect, 0, 0, winSize.x, winSize.y);
	AdjustWindowRect(&rect, winStyle, FALSE);

	int sysWidth = GetSystemMetrics(SM_CXSCREEN);
	int sysHeight = GetSystemMetrics(SM_CXSCREEN);

	handle = CreateWindow//프로그램의 식별자
	(
		className
		, title
		, winStyle
		, (sysWidth - (rect.right - rect.left))/2
		, (sysHeight - (rect.bottom - rect.top))/2
		, (rect.right - rect.left)
		, (rect.bottom - rect.top)
		, NULL
		, NULL
		, instance
		, NULL
	);
	assert(handle != NULL);
}

void DxWindow::CreateDevice()
{
	D3DPRESENT_PARAMETERS d3dParam;
	ZeroMemory(&d3dParam, sizeof(d3dParam));//memset간략함.
	//값 설정하기.
	d3dParam.Windowed = isWindow;//윈도우 모드 or 풀 스크린 인지 선택.
	d3dParam.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dParam.EnableAutoDepthStencil = TRUE;
	d3dParam.AutoDepthStencilFormat = D3DFMT_D16;

	d3d = Direct3DCreate9(D3D_SDK_VERSION);//9버전에서 최신버전으로 들어감.
	assert(d3d != NULL);

	D3DCAPS9 caps;
	d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	HRESULT hr = d3d->CreateDevice
	(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		handle,//윈도우
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dParam, &device
	);
	assert(hr == S_OK);

	ShowWindow(handle, SW_SHOW);
	UpdateWindow(handle);
	ShowCursor(isShowCursor);

}

WPARAM DxWindow::Run()
{
	MSG message;
	ZeroMemory(&message, sizeof(message));
	
	Initialize();//초기화 할 함수

	while (GetMessage(&message, NULL, 0, 0)) {
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else {
			Update();
			Render();
		}
	}

	Destroy();

	UnregisterClass(className, instance);
	return message.wParam;
}

LRESULT DxWindow::MessageLoop(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {

	HDC hdc;

	switch (message)
	{
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE) {
				SendMessage(hwnd, WM_DESTROY, 0, 0);
				break;
			}

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

int WINAPI WinMain
(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	
	GameMain main(hInstance, L"DxClass", lpszCmdParam, nCmdShow);
	main.Create(L"DirectX");
	main.CreateDevice();

	return main.Run();
}