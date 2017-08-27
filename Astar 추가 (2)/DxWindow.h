#pragma once

class DxWindow
{
protected:
	static DxWindow* dxWindow;

	HINSTANCE instance;
	LPWSTR className;
	LPSTR commandLine;
	int commandShow;

	HWND handle;
	HWND handle2;


	//POINT winSize = { 1000, 800 };
	POINT winSize = { 1280, 720 };
	DWORD winStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

	BOOL isWindow = TRUE;
	BOOL isShowCursor = TRUE;

	LPDIRECT3D9	d3d = NULL;

	LPDIRECT3DDEVICE9 device = NULL;

	LPDIRECT3DSWAPCHAIN9 chain1 = NULL;
	LPDIRECT3DSWAPCHAIN9 chain2 = NULL;

	int g_scrollBarPosY = 0;						// Set the current scroll bar position to 0


public:
	// 객체 생성자
	DxWindow(HINSTANCE hInstance, LPCWSTR className, LPCSTR lpCmdLine, int nCmdShow);
	// 객체 파괴자
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
};