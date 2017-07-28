#pragma once
class Rect
{
public:
	Rect(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 coord, D3DXVECTOR2 size, DWORD color = 0xFF000000);
	~Rect();

	RECT GetRect();
	D3DXVECTOR2 GetCoord() { return coord; }
	DWORD Getcolor() { return lineColor; }

	void SetCoord(D3DXVECTOR2 coord);
	void SetScale(const D3DXVECTOR2* scale);
	void SetRotate(float angle);
	void SetColor(DWORD color) { lineColor = color; }

	void Initialize();
	void Destroy();
	void Update();
	void Render();



private:
	void AdjustTransform();

	LPDIRECT3DDEVICE9 device;
	LPD3DXLINE line;
	DWORD lineColor;
	D3DXVECTOR3 lineVector[5];
	
	D3DXVECTOR2 coord;
	D3DXVECTOR2 size;
	D3DXVECTOR2 scale;
	float angle;

	D3DXMATRIX world;
};