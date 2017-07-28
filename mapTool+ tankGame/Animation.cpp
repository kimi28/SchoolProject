#include "stdafx.h"
#include "Animation.h"
#include "Texture.h"
#include "Rect.h"

Animation::Animation(LPDIRECT3DDEVICE9 device, WCHAR* fileName, D3DXVECTOR2 Maxframe,
	D3DXVECTOR2 coord, D3DXVECTOR2 size, D3DXVECTOR2 scale)
	: device(device)
	, maxframe(Maxframe)
	, coord(coord)
	, size(size)
	, angle(0)
	, scale(scale)
{
	wcscpy(this->fileName, fileName);

	D3DXMatrixIdentity(&world);

	Initialize();
}


Animation::~Animation()
{
	Destroy();
}

void Animation::Initialize()
{

	HRESULT hr;
	hr = D3DXCreateSprite(device, &sprite);
	assert(SUCCEEDED(hr));

	texture = new Texture(device, fileName);

	size.x = (size.x < 1) ? texture->GetWidth() : size.x;
	size.y = (size.y < 1) ? texture->GetHeight() : size.y;


	drawSize.x = size.x / maxframe.x;
	drawSize.y = size.y / maxframe.y;

	rect = new Rect(device, coord, D3DXVECTOR2(drawSize.x,drawSize.y));

	AdjustTransform();
}

void Animation::Destroy()
{
	SAFE_DELETE(texture);
	rect->Destroy();
	SAFE_DELETE(rect);
}

void Animation::Update(POINT currentframe)
{

	if (currentframe.x > maxframe.x)
	{
		currentframe.x = maxframe.x;
	}
	if (currentframe.y > maxframe.y)
	{
		currentframe.y = maxframe.y;
	}

	POINT drawStart;
	drawStart.x = drawSize.x * currentframe.x;
	drawStart.y = drawSize.y * currentframe.y;

	POINT drawEnd;

	drawEnd.x = drawSize.x * currentframe.x + drawSize.x;
	drawEnd.y = drawSize.y * currentframe.y + drawSize.y;


	drawRect = { drawStart.x, drawStart.y,drawEnd.x,drawEnd.y };

	rect->SetCoord(coord);
}

void Animation::Render()
{

	sprite->SetTransform(&world);
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture->GetTexture(), &drawRect, NULL,NULL, 0xFFFFFFFF);
	sprite->End();

	
}

void Animation::SetCoord(D3DXVECTOR2 coord)
{
	this->coord = coord;

	AdjustTransform();
}

void Animation::AdjustTransform()
{
	D3DXMatrixIdentity(&world);

	float angle = D3DXToRadian(this->angle);
	D3DXMATRIX scale;
	D3DXMATRIX rotation;
	D3DXMATRIX rotationCenter;
	D3DXMATRIX rotationInverseCenter;
	D3DXMATRIX translate;

	D3DXMatrixIdentity(&scale);
	D3DXMatrixIdentity(&rotation);
	D3DXMatrixIdentity(&rotationCenter);
	D3DXMatrixIdentity(&rotationInverseCenter);
	D3DXMatrixIdentity(&translate);


	D3DXMatrixScaling(&scale, this->scale.x, this->scale.y, 1.0f);

	D3DXVECTOR2 center;
	center.x = size.x * 0.5f;
	center.y = size.y * 0.5f;

	D3DXMatrixTranslation(&rotationInverseCenter, -center.x, -center.y, 0);
	{
		D3DXMatrixRotationZ(&rotation, -angle);
	}
	D3DXMatrixTranslation(&rotationCenter, center.x, center.y, 0);
	D3DXMatrixTranslation(&translate, FLOAT(coord.x), FLOAT(coord.y), 0);


	world = scale * rotationInverseCenter * rotation *
		rotationCenter * translate;
}

