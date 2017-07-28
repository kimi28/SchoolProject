#pragma once

class Texture;
class Sprite
{
public:
	Sprite();
	Sprite(LPDIRECT3DDEVICE9 device, WCHAR* fileName,
		D3DXVECTOR2 coord = D3DXVECTOR2(0, 0), D3DXVECTOR2 size = D3DXVECTOR2(0, 0), D3DXVECTOR2 scale = D3DXVECTOR2(1, 1)); // 스케일은 무조건 1, 0이 될 수 없음
	~Sprite();

	D3DXVECTOR2 GetCoord() { return coord; }
	D3DXVECTOR2 GetRealSize();

	D3DXVECTOR2 GetSize() { return size; }
	D3DXVECTOR2 GetSizeHalf() { D3DXVECTOR2 halfSize(size.x * 0.5f, size.y * 0.5f); return halfSize; }
	

	void SetCoord(D3DXVECTOR2 coord);
	void SetScale(D3DXVECTOR2 scale);
	void SetRotate(float angle);

	void Initialize();
	void Destory();
	void Update();
	void Render();

private:
	void AdjustTransform();

	LPDIRECT3DDEVICE9 device;
	LPD3DXSPRITE sprite;
	Texture* texture;

	WCHAR fileName[255];
	D3DXVECTOR2 coord;
	D3DXVECTOR2 size;
	D3DXVECTOR2 scale;
	float angle;

	D3DXMATRIX world;
};

