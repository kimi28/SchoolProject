#include "stdafx.h"
#include "DebugGrid.h"

DebugGrid* DebugGrid::instance = NULL;

DebugGrid * DebugGrid::GetInstance()
{
	if (instance == NULL)
		instance = new DebugGrid();

	return instance;
}

void DebugGrid::DeleteInstance()
{
	SAFE_DELETE(instance);
}

void DebugGrid::SetDevice(LPDIRECT3DDEVICE9 device)
{
	this->device = device;

	HRESULT hr;
	hr = D3DXCreateLine(device, &line);

	line->SetPattern(0x55555555);
	line->SetPatternScale(1.0f);
	SetSpace({ 50,50 });


}

void DebugGrid::Render(bool isDraw)
{
	if (isDraw == false) return;

	D3DVIEWPORT9 viewport;
	device->GetViewport(&viewport);

	int v = viewport.Width / space.x;
	int h = viewport.Height / space.y;

	line->Begin();
	D3DXVECTOR2 drawLine[2];
	for (int i = 0; i <= v; i++) {
		drawLine[0] = D3DXVECTOR2(i*space.x, 0);
		drawLine[1] = D3DXVECTOR2(i*space.x, viewport.Height);
		line->Draw(drawLine, 2, color);
	}

	for (int i = 0; i <= h; i++) {
		drawLine[0] = D3DXVECTOR2(0, i * space.y);
		drawLine[1] = D3DXVECTOR2(viewport.Width, i * space.y);
		line->Draw(drawLine, 2, color);
	}
	line->End();
}

DebugGrid::DebugGrid()
	: device(NULL)
	, line(NULL)
	, color(0xFFAAAAAA)
{
}


DebugGrid::~DebugGrid()
{
	SAFE_RELEASE(line);
}
