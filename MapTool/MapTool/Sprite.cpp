#include "stdafx.h"
#include "Sprite.h"
#include "Texture.h"

Sprite::Sprite()
{

}

Sprite::Sprite(LPDIRECT3DDEVICE9 device, WCHAR* fileName,
	D3DXVECTOR2 coord, D3DXVECTOR2 size, D3DXVECTOR2 scale)
	: device(device)
	, coord(coord)
	, size(size)
	, sprite(NULL)
	, texture(NULL)
	, angle(0)
	, scale(scale)
{
	wcscpy(this->fileName, fileName);

	D3DXMatrixIdentity(&world);
}


Sprite::~Sprite()
{
}

D3DXVECTOR2 Sprite::GetRealSize()
{
	D3DXVECTOR2 temp;
	temp.x = size.x * scale.x;
	temp.y = size.y * scale.y;

	return temp;
}

void Sprite::SetCoord(D3DXVECTOR2 coord)
{
	this->coord = coord;

	AdjustTransform();
}

void Sprite::SetScale(D3DXVECTOR2 scale)
{
	this->scale = scale;

	size.x = texture->GetWidth() * scale.x;
	size.y = texture->GetHeight() * scale.y;

	AdjustTransform();
}

void Sprite::SetRotate(float angle)
{
	this->angle = angle;

	AdjustTransform();

}

void Sprite::Initialize()
{
	HRESULT hr;
	hr = D3DXCreateSprite(device, &sprite);
	assert(SUCCEEDED(hr));

	texture = new Texture(device, fileName);

	assert(SUCCEEDED(hr));

	size.x = (size.x < 1) ? texture->GetWidth() : size.x;
	size.y = (size.y < 1) ? texture->GetHeight() : size.y;

	AdjustTransform();

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
	//RECT rect;
	//texture->GetRect(&rect);

	//static bool isCheck = false;
	//if (Keyboard::GetInstance()->KeyDown(VK_1))
	//	isCheck = !isCheck;

	//D3DXMATRIX world;
	//D3DXMatrixIdentity(&world);
	//if (isCheck) {
	//	world._11 = 2.0f;
	//	world._22 = 2.0f;
	//}
	//else {
	//	world._11 = 1.0f;
	//	world._22 = 1.0f;
	//}
	//world._41 = texture->GetHalfWidth() + (rect.right - rect.left);
	//world._42 = texture->GetHalfHeight() + (rect.bottom - rect.top);

	sprite->SetTransform(&world);
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	sprite->Draw(texture->GetTexture()
		, &texture->GetRect()
		, NULL
		, NULL
		, 0xFFFFFFFF);

	sprite->End();
}

void Sprite::AdjustTransform()
{
	D3DXMatrixIdentity(&world);

	float angle = D3DXToRadian(this->angle);
	D3DXMATRIX scale;//크기
	D3DXMATRIX rotation;//회전
	D3DXMATRIX rotationCenter;
	D3DXMATRIX rotationInverseCenter;
	D3DXMATRIX translate;//이동

	D3DXMatrixIdentity(&scale);
	D3DXMatrixIdentity(&rotation);
	D3DXMatrixIdentity(&rotationCenter);
	D3DXMatrixIdentity(&rotationInverseCenter);
	D3DXMatrixIdentity(&translate);

	D3DXMatrixScaling(&scale, this->scale.x, this->scale.y, 1.0f);

	D3DXVECTOR2 center;
	center.x = size.x*0.5f;
	center.y = size.y* 0.5f;
	D3DXMatrixTranslation(&rotationInverseCenter
		, -center.x
		, -center.y
		, 0);
	{
		D3DXMatrixRotationZ(&rotation, -angle);
	}
	D3DXMatrixTranslation(&rotationCenter, center.x, center.y, 0);

	D3DXMatrixTranslation(&translate
		, FLOAT(coord.x)
		, FLOAT(coord.y)
		, 0);

	world = scale * rotationInverseCenter 
		* rotation * rotationCenter * translate;
}