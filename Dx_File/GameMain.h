#pragma once
#include "DxWindow.h"

class GameMain :public DxWindow
{
private:

public:
	GameMain(HINSTANCE hInstanece, LPCWSTR className, LPCSTR lpCmdLine, int nCmdShow);
	~GameMain();

	void Initialize();
	void Update();
	void Render();
	void Destroy();
};