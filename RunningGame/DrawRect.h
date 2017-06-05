#pragma once
class DrawRect
{
public:
	DrawRect(LPDIRECT3DDEVICE9 device, POINT coord, POINT size, DWORD color = 0xFF000000);
	~DrawRect();

	RECT GetRect() { return rect; }
	POINT GetCoord() { return coord; }
	DWORD GetColor() { return lineColor; }
	POINT GetSize() { return size; }

	void SetCoord(POINT coord);
	void SetColor(DWORD color) { lineColor = color; }
	
	void Initialize();
	void Destroy();
	void Update();
	void Render();

private:
	void AdjustDrawVec();

	LPDIRECT3DDEVICE9 device;
	LPD3DXLINE line;
	D3DXVECTOR2 drawVec[5];
	DWORD lineColor;

	RECT rect;
	POINT coord;
	POINT size;
};

