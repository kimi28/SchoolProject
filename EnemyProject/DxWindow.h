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

	POINT winSize = { 1024, 768 };
	//POINT winSize = { 1280, 720 };
	DWORD winStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

	BOOL isWindow = TRUE;
	BOOL isShowCursor = TRUE;

	LPDIRECT3D9	d3d = NULL;
	LPDIRECT3DDEVICE9 device = NULL;

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