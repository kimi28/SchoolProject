#include "stdafx.h"
#include "Sprite.h"
#include "Texture.h"



Sprite::Sprite(LPDIRECT3DDEVICE9 device, WCHAR* fileName, POINT coord, POINT size)
	: device(device)
	, coord(coord)
	, size(size)
	, sprite(NULL)
	, texture(NULL)
{
	wcscpy(this->fileName, fileName);
}


Sprite::~Sprite()
{
}

void Sprite::Initialize()
{
	HRESULT hr;
	hr = D3DXCreateSprite(device, &sprite);
	assert(SUCCEEDED(hr));

	texture = new Texture(device, fileName);

	assert(SUCCEEDED(hr));

	size.x = (size.x < 1 ) ? texture->GetWidth() : size.x;
	size.y = (size.y < 1) ? texture->GetHeight() : size.y;
}

void Sprite::Destroy()
{
	SAFE_DELETE(texture);
	SAFE_RELEASE(sprite);
}

void Sprite::Update()
{
}

void Sprite::Render()
{
	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);
	world._11 = 2.0f;
	world._22 = 2.0f;

	D3DXVECTOR3 point = D3DXVECTOR3(coord.x, coord.y, 0);

	sprite->SetTransform(&world);
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	sprite->Draw(texture->GetTexture(), NULL, NULL, &point, 0xFFFFFFFF);

	sprite->End();
}
