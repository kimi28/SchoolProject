#pragma once
class Cube;
class ColorShader;
class MainGame
{
	Cube* model[6];
	ColorShader* colorShader;
public:
	MainGame();
	~MainGame();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

public:
	//���ν���
	LRESULT MainProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lparam);
};

