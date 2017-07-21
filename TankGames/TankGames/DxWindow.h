#pragma once

class DxWindow
{
public:
	// ��ü ������
	DxWindow(HINSTANCE hInstance, LPCWSTR className, LPCSTR lpCmdLine, int nCmdShow);
	// ��ü �ı���
	virtual ~DxWindow();

	static DxWindow* GetDxWindow() { return dxWindow; }

	void Create(LPCWSTR title);


	void CreateDevice();

	WPARAM Run();


	LRESULT MessageLoop(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);





	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;

protected:
	static DxWindow* dxWindow;

	HINSTANCE instance;
	LPWSTR className;
	LPSTR commandeLine;
	int commandShow;

	HWND handle;
	HWND handle2;

	POINT winSize = { 1024 + 480, 768 };
	DWORD winStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

	BOOL isWindow = TRUE;
	BOOL isShowCursor = TRUE;

	LPDIRECT3D9 d3d = NULL;

	LPDIRECT3DDEVICE9 device = NULL;

	LPDIRECT3DSWAPCHAIN9 chain1 = NULL;
	LPDIRECT3DSWAPCHAIN9 chain2 = NULL;

	int g_scrollBarPosY = 0;

};

