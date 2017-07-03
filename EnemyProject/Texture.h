#pragma once
class Texture
{
public:
	Texture(LPDIRECT3DDEVICE9 device, WCHAR* fileName, 
		DWORD color = 0xFFFFFFFF, DWORD colorKey = 0x00FFFFFF);
	~Texture();

	int GetWidth() { return imageInfo.Width; }
	int GetHeight() { return imageInfo.Height; }
	int GetHalfWidth() { return (int)(imageInfo.Width * 0.5f); }
	int GetHalfHeight() { return (int)(imageInfo.Height * 0.5f); }
	
	RECT GetRect();

	LPDIRECT3DTEXTURE9 GetTexture() { return texture; }

private:
	LPDIRECT3DDEVICE9 device;
	
	WCHAR fileName[255];
	D3DXIMAGE_INFO imageInfo;
	LPDIRECT3DTEXTURE9 texture;

	DWORD color;
	DWORD colorKey;
};