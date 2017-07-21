#pragma once
class DebugGrid
{
public:
	static DebugGrid* GetInstance();
	static void DeleteInstance();

	void SetDevice(LPDIRECT3DDEVICE9 device);
	void SetSpace(POINT space) { this->space = space; }
	void SetColor(DWORD color) { this->color = color; }

	void Render(bool isDraw = false);

private:
	DebugGrid();
	~DebugGrid();

	static DebugGrid* instance;

	LPDIRECT3DDEVICE9 device;
	LPD3DXLINE line;
	DWORD color;

	POINT space;
};

