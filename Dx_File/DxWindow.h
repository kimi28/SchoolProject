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
	DWORD winStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

	BOOL isWindow = TRUE;
	BOOL isShowCursor = TRUE;

	LPDIRECT3D9 d3d = NULL;
	LPDIRECT3DDEVICE9 device = NULL;//Dx 랩핑하는 명령을 내린다.

public:
	//객체 생성자
	DxWindow(HINSTANCE hInstance, LPCWSTR lpClassName, LPCSTR lpCmdLine, int nCmdShow);
	//객체 파괴자
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
	//추상 클래스는 몸체가 없어서 객체로 사용 할 수 없음.
};