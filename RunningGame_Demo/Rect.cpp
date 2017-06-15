#include "stdafx.h"
#include "Rect.h"



Rect::Rect(LPDIRECT3DDEVICE9 device, POINT coord, POINT size, DWORD color)
	: device(device)
	, lineColor(color)
	, coord(coord)
	, size(size)
{
	rect = { 0 };
}


Rect::~Rect()
{
}

void Rect::SetCoord(POINT coord)
{
	this->coord = coord;

	AdjustDrawVec();

}

void Rect::Initialize()
{
	HRESULT hr;
	hr = D3DXCreateLine(device, &line);
	assert(SUCCEEDED(hr));

	AdjustDrawVec();

}

void Rect::Destroy()
{
	SAFE_RELEASE(line);
}

void Rect::Update()
{

}

void Rect::Render()
{
	line->Begin();
	line->Draw(drawVec, 5, lineColor);
	line->End();
}

void Rect::AdjustDrawVec()
{
	rect.left = coord.x;
	rect.top = coord.y;
	rect.right = coord.x + size.x;
	rect.bottom = coord.y + size.y;

	drawVec[0] = D3DXVECTOR2(rect.left, rect.top);
	drawVec[1] = D3DXVECTOR2(rect.right, rect.top);
	drawVec[2] = D3DXVECTOR2(rect.right, rect.bottom);
	drawVec[3] = D3DXVECTOR2(rect.left, rect.bottom);
	drawVec[4] = D3DXVECTOR2(rect.left, rect.top);
}
