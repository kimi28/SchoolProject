#pragma once
class Texture;
class Sprite
{
public:
	Sprite(LPDIRECT3DDEVICE9 device, WCHAR* fileName,
		POINT coord, POINT size = { 0,0 });
	~Sprite();

	void Initialize();
	void Destroy();
	void Update();
	void Render();

private:
	LPDIRECT3DDEVICE9 device;
	LPD3DXSPRITE sprite;
	Texture* texture;

	WCHAR fileName[255];
	POINT coord;
	POINT size;
};

