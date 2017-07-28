#include "stdafx.h"
#include "Circle.h"

Circle::Circle(LPDIRECT3DDEVICE9 device, POINT coord, 
	float radius, int side, DWORD color)
	: side(side)
	, color(color)
	, coord(coord)
	, radius(radius)
	, drawCount(0)
{
	this->device = device;

	ZeroMemory(drawVec, sizeof(drawVec));
}

Circle::~Circle()
{
	
}

void Circle::SetCoord(POINT coord)
{
	this->coord = coord;

	AdjustDrawVec();
}

void Circle::SetRadius(float radius)
{
	this->radius = radius;

	AdjustDrawVec();
}

void Circle::Initialize()
{
	HRESULT hr;
	hr = D3DXCreateLine(device, &line);
	assert(SUCCEEDED(hr));

	line->SetAntialias(TRUE);

	AdjustDrawVec();
}

void Circle::Destroy()
{
	SAFE_RELEASE(line);
}

void Circle::Update()
{
	
}

void Circle::Render()
{
	line->Begin();
	line->Draw(drawVec, drawCount, color);
	line->End();
}

void Circle::AdjustDrawVec()
{
	drawCount = 0;
	float step = PI * 2.0f / side;
	for (float i = 0; i < PI * 2.0f; i += step)
	{
		D3DXVECTOR2 v1;
		D3DXVECTOR2 v2;

		v1.x = radius * cos(i) + coord.x;
		v1.y = radius * sin(i) + coord.y;
		v2.x = radius * cos(i + step) + coord.x;
		v2.y = radius * sin(i + step) + coord.y;

		drawVec[drawCount] = v1;
		drawVec[drawCount + 1] = v2;

		drawCount += 2;
	}
}
