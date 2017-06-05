#include "stdafx.h"
#include "DrawCircle.h"



DrawCircle::DrawCircle(LPDIRECT3DDEVICE9 device, POINT coord, float radius,
	int side, DWORD color)
	: device(device)
	, coord(coord)
	, radius(radius)
	, side(side)
	, color(color)
	, drawCount(0)
{
	ZeroMemory(drawVec, sizeof(drawVec));
}

DrawCircle::~DrawCircle()
{
}

void DrawCircle::SetCoord(POINT coord)
{
	this->coord = coord;

	AdjustDrawVec();
}

void DrawCircle::SetRadius(float radius)
{
	this->radius = radius;

	AdjustDrawVec();
}

void DrawCircle::Initalize()
{
	HRESULT hr;
	hr = D3DXCreateLine(device, &line);
	assert(SUCCEEDED(hr));

	line->SetAntialias(TRUE);

	AdjustDrawVec();
}

void DrawCircle::Destroy()
{
	SAFE_RELEASE(line);
}

void DrawCircle::Update()
{
}

void DrawCircle::Render()
{
	line->Begin();
	line->Draw(drawVec, drawCount, color);
	line->End();
}

void DrawCircle::AdjustDrawVec()
{
	float step = PI * 2.0f / side;
	for (float i = 0; i < PI * 2.0f; i += step) {
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