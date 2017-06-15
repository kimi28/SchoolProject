#pragma once
class Texture
{
public:
	Texture(LPDIRECT3DDEVICE9 device, WCHAR* fileName, 
		DWORD color = 0xFFFFFFFF, DWORD colorKey = 0x00FFFFFF);
	~Texture();

	int GetWidth() { return imageInfo.Width; }
	int GetHeight() { return imageInfo.Height; }
	void GetRect(RECT* rect);

	LPDIRECT3DTEXTURE9 GetTexture() { return texture; }

private:
	LPDIRECT3DDEVICE9 device;
	
	WCHAR fileName[255];
	D3DXIMAGE_INFO imageInfo;
	LPDIRECT3DTEXTURE9 texture;

	DWORD color;
	DWORD colorKey;
};