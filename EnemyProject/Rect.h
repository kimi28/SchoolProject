#pragma once
class Rect
{
public:
	Rect(LPDIRECT3DDEVICE9 device, POINT coord, 
		POINT size, DWORD color = 0xFF000000);
	~Rect();
	
	RECT GetRect();

	POINT GetCoord() { return coord; }
	DWORD GetColor() { return lineColor; }

	void SetCoord(POINT coord);
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

	POINT coord;
	POINT size;
	D3DXVECTOR2 scale;
	float angle;

	D3DXMATRIX world;
};

