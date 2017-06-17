#pragma once
class Circle
{
public:
	Circle(LPDIRECT3DDEVICE9 device, POINT coord, float radius,
		int side = 20, DWORD color = 0xFF000000);
	~Circle();

	POINT GetCoord() { return coord; }
	float GetRadius() { return radius; }
	DWORD GetColor() { return color; }

	void SetCoord(POINT coord);
	void SetRadius(float radius);
	void SetColor(DWORD color) { this->color = color; }

	void Initalize();
	void Destroy();
	void Update();
	void Render();

private:
	void AdjustDrawVec();

	LPDIRECT3DDEVICE9 device;
	LPD3DXLINE line;
	int side;
	DWORD color;

	D3DXVECTOR2 drawVec[128];
	int drawCount;

	POINT coord;
	float radius;
};

