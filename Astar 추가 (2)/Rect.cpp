#include "stdafx.h"
#include "Rect.h"
#include "InterSect.h"

Rect::Rect(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 coord, D3DXVECTOR2 size, DWORD color)
	: device(device)
	, lineColor(color)
	, coord(coord)
	, size(size)
	, angle(0)
	, scale(1, 1)
{
	Initialize();
	D3DXMatrixIdentity(&world);
}

Rect::~Rect()
{
}

RECT Rect::GetRect()
{
	RECT rect =
	{
		coord.x,
		coord.y,
		coord.x + size.x,
		coord.y + size.y
	};

	return rect;
}

void Rect::SetCoord(D3DXVECTOR2 coord)
{
	this->coord = coord;

	AdjustTransform();
}

void Rect::SetScale(const D3DXVECTOR2 * scale)
{
	if (this->scale == *scale)
		return;

	this->scale = *scale;

	size.x = size.x * scale->x;
	size.y = size.y * scale->y;

	AdjustTransform();
}

void Rect::SetRotate(float angle)
{
	this->angle = angle;

	AdjustTransform();
}

void Rect::Initialize()
{
	HRESULT hr;
	hr = D3DXCreateLine(device, &line);
	assert(SUCCEEDED(hr));

	AdjustTransform();
}

void Rect::Destroy()
{
	line->Release();
}

void Rect::Update()
{

}

void Rect::Render()
{
	D3DVIEWPORT9 viewport;
	device->GetViewport(&viewport);


	D3DXMATRIX ortho;
	D3DXMatrixOrthoOffCenterLH(&ortho, 0, viewport.Width, viewport.Height, 0, 0, 1);

	line->Begin();
	line->DrawTransform(lineVector, 5, &ortho, lineColor);
	line->End();
}

void Rect::AdjustTransform()
{
	lineVector[0] = D3DXVECTOR3(0, 0, 0);
	lineVector[1] = D3DXVECTOR3(size.x, 0, 0);
	lineVector[2] = D3DXVECTOR3(size.x, size.y, 0);
	lineVector[3] = D3DXVECTOR3(0, size.y, 0);
	lineVector[4] = D3DXVECTOR3(0, 0, 0);

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

	for (int i = 0; i < 5; i++)
		D3DXVec3TransformCoord(&lineVector[i], &lineVector[i], &world);
}
