#pragma once
class Cube;
class ColorShader;
class MainGame
{
	Cube* model;
	ColorShader* colorShader;

public:
	MainGame();
	~MainGame();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

public: 
	LRESULT MainProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

