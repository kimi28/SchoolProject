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
	//���ν���
	LRESULT MainProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lparam);
};

