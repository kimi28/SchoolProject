#pragma once
class Rect
{
public:
	Rect(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 coord, D3DXVECTOR2 size, DWORD color = 0xFF000000);
	~Rect();

	RECT GetRect() { return rect; }
	D3DXVECTOR2 GetCoord() { return coord; }
	DWORD GetColor() { return lineColor; }

	void SetCoord(D3DXVECTOR2 coord);
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
	D3DXVECTOR2 coord;
	D3DXVECTOR2 size;

};

