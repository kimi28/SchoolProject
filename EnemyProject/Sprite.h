#pragma once
class Texture;
class Sprite
{
public:
	Sprite();
	Sprite(LPDIRECT3DDEVICE9 device, 
		WCHAR* fileName,
		D3DXVECTOR2 coord = D3DXVECTOR2(0,0), 
		D3DXVECTOR2 size = D3DXVECTOR2(0, 0),
		D3DXVECTOR2 scale = D3DXVECTOR2(1, 1));
	~Sprite();

	D3DXVECTOR2 GetCoord() { return coord; }
	D3DXVECTOR2 GetSize() { return size; }
	D3DXVECTOR2 GetRealSize();

	void SetCoord(D3DXVECTOR2 coord);
	void SetScale(D3DXVECTOR2 scale);
	void SetRotate(float angle);
	
	void Initialize();
	void Destroy();
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

