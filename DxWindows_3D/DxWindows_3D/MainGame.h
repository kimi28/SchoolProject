#pragma once

class Scene;

class MainGame
{
	Scene*		nowScene;

public:
	MainGame();
	~MainGame();

	HRESULT Init();
	void Realese();
	void Update();
	void Render();

public:
	//프로시져
	LRESULT MainProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lparam);
};

