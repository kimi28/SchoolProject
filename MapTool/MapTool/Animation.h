#pragma once
class Texture;
class Rect;
class Animation
{
public:
	Animation(LPDIRECT3DDEVICE9 device, WCHAR* fileName,
		D3DXVECTOR2 maxFrame, D3DXVECTOR2 coord, D3DXVECTOR2 size = D3DXVECTOR2(0,0),
		D3DXVECTOR2 scale = D3DXVECTOR2(1,1));
	~Animation();

	Rect* GetRect() { return rect; }

	void Initialize();
	void Destroy();
	void Update(POINT currentFrame);
	void Render();

	void SetCoord(D3DXVECTOR2 coord);
	void AdjustTransform();

private:
	LPDIRECT3DDEVICE9 device;
	LPD3DXSPRITE sprite;
	Texture* texture;
	Rect* rect;

	WCHAR fileName[255];
	D3DXVECTOR2 maxFrame;
	D3DXVECTOR2 coord;
	D3DXVECTOR2 size;
	D3DXVECTOR2 scale;

	POINT drawSize;
	float angle;
	RECT drawRect;

	D3DXMATRIX world;
};

