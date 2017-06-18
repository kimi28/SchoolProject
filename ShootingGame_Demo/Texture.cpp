#include "stdafx.h"
#include "Texture.h"



Texture::Texture(LPDIRECT3DDEVICE9 device, WCHAR* fileName, 
	DWORD color, DWORD colorKey)
	: device(device)
	, colorKey(colorKey)
{
	wcscpy(this->fileName, fileName);

	HRESULT hr;
	hr = D3DXCreateTextureFromFileEx(
		device
		, fileName
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 1
		, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, 0x01
		, 0x01
		, colorKey
		, &imageInfo
		, NULL
		, &texture
	);
	assert(SUCCEEDED(hr));
}


Texture::~Texture()
{
	SAFE_RELEASE(texture);
}

RECT Texture::GetRect()
{
	RECT rect;
	
	rect.left = 0;
	rect.top = 0;
	rect.right = imageInfo.Width;
	rect.bottom = imageInfo.Height;

	return rect;
}
