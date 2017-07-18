#include "stdafx.h"
#include "DxWindow.h"
#include "GameMain.h"

DxWindow* DxWindow::dxWindow = NULL;

GameMain* main;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Mouse::GetInstance()->InputProc(uMsg, wParam, lParam);

	return DxWindow::GetDxWindow()->MessageLoop(hWnd, uMsg, wParam, lParam);
}

DxWindow::DxWindow(HINSTANCE hInstance, LPCWSTR lpClassName, LPCSTR lpszCmdParam, int nCmdShow)
{
	dxWindow = this;

	commandShow = nCmdShow;
	instance = hInstance;
	handle = NULL;

	if (lpClassName != NULL)
	{
		int length = wcslen(lpClassName) + 1;

		className = new WCHAR[length];
		wcscpy_s(className, length, lpClassName);
	}
	else
	{
		className = NULL;
	}

	if (lpszCmdParam != NULL)
	{
		int length = strlen(lpszCmdParam) + 1;

		commandLine = new char[length];
		strcpy_s(commandLine, length, lpszCmdParam);
	}
	else
	{
		commandLine = NULL;
	}
}

DxWindow::~DxWindow()
{
	SAFE_DELETE(main);
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
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = instance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = className;
	wndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;

	ATOM result = RegisterClass(&wndClass);
	assert(result != 0);


	RECT rect;
	SetRect(&rect, 0, 0, winSize.x, winSize.y);
	AdjustWindowRect(&rect, winStyle, FALSE);

	int sysWidth = GetSystemMetrics(SM_CXSCREEN);
	int sysHeight = GetSystemMetrics(SM_CYSCREEN);

	handle = CreateWindow
	(
		className
		, title
		, winStyle
		, (sysWidth - (rect.right - rect.left)) / 2
		, (sysHeight - (rect.bottom - rect.top)) / 2
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
	ZeroMemory(&d3dParam, sizeof(d3dParam));

	d3dParam.Windowed = isWindow;
	d3dParam.SwapEffect = D3DSWAPEFFECT_DISCARD; //�ø��� ����ۿ� ������ ���� �ʴ´�.
	d3dParam.EnableAutoDepthStencil = TRUE; //���� ���ٽ� ���� �ڵ� ����
	d3dParam.AutoDepthStencilFormat = D3DFMT_D16; //���� ����


	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	assert(d3d != NULL);

	D3DCAPS9 caps;
	d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	HRESULT hr = d3d->CreateDevice
	(
		D3DADAPTER_DEFAULT, //��� ����� �� ����Ʈ ����͸� ���
		D3DDEVTYPE_HAL, //����Ʈ����� �ϵ���� ���� ������ ���
		handle, //������ �ڵ�
		D3DCREATE_HARDWARE_VERTEXPROCESSING, //���� ������ �ϵ����� ó��
		&d3dParam, &device
	);
	assert(SUCCEEDED(hr));


	ShowWindow(handle, SW_SHOW); //�� ����� �����ϱ� ������ ���
	UpdateWindow(handle); //������ ����
	ShowCursor(isShowCursor); //Ŀ�� ����
}

WPARAM DxWindow::Run()
{
	MSG message;
	ZeroMemory(&message, sizeof(message));

	Mouse::GetInstance()->SetHandle(handle);
	DebugGrid::GetInstance()->SetDevice(device);
	PrintText::GetInstance()->SetDevice(device);
	SoundManager::GetInstance()->Initialize();



	Initialize();

	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			Keyboard::GetInstance()->Update();
			Mouse::GetInstance()->Update();
			//Timer::GetInstance()->Tick(60.f);
			SoundManager::GetInstance()->Update();

			Update();

			device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(1, 1, 1, 1), 1.0f, 0);

			device->BeginScene();
			{
				DebugGrid::GetInstance()->Render(true);


				Render();

				//Timer::GetInstance()->Render();
				PrintText::GetInstance()->Render();
			}
			device->EndScene();
			device->Present(0, 0, 0, 0);
		}
	}

	Destroy();

	PrintText::DeleteInstance();
	DebugGrid::DeleteInstance();
	Keyboard::DeleteInstance();
	Mouse::DeleteInstance();
	//Timer::DeleteInstance();
	SoundManager::DeleteInstance();

	UnregisterClass(className, instance);
	return message.wParam;
}

LRESULT DxWindow::MessageLoop(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_FILE_SAVE:
			MessageBox(hwnd, TEXT("Save�Ͽ����ϴ�."), TEXT("Save"), MB_OK);
			main->Save();
			break;
		case ID_FILE_LOAD:
			MessageBox(hwnd, TEXT("Load�Ͽ����ϴ�."), TEXT("Load"), MB_OK);
			main->Load();
			break;
		case ID_TILE_OBJECT:
			MessageBox(hwnd, TEXT("Object�� �����Ͽ����ϴ�."), TEXT("Object"), MB_OK);
			main->SetCtrSelect(CTRL_OBJDRAW);
			break;
		case ID_TILE_TERRAIN:
			MessageBox(hwnd, TEXT("Terrain�� �����Ͽ����ϴ�."), TEXT("Terrain"), MB_OK);
			main->SetCtrSelect(CTRL_TERRAINDRAW);
			break;
		case ID_FILE_EXIT:
			PostQuitMessage(0);
			break;
		}
	}
	case WM_KEYDOWN:
	{
		if (wParam == VK_ESCAPE)
		{
			SendMessage(hwnd, WM_DESTROY, 0, 0);
			break;
		}

		return 0;
	}

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	 main = new GameMain(hInstance, L"DxClass", lpszCmdParam, nCmdShow);
	main->Create(L"DirectX");
	main->CreateDevice();

	return main->Run();
}