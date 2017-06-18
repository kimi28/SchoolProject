#pragma once
class Texture;
class Sprite
{
public:
	Sprite(LPDIRECT3DDEVICE9 device, WCHAR* fileName,
		POINT coord, POINT size = { 0,0 });
	~Sprite();

	void SetCoord(POINT coord);
	void SetScale(const D3DXVECTOR2* scale);
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
	POINT coord;
	POINT size;

	D3DXVECTOR2 scale;
	float angle;

	D3DXMATRIX world;
};

