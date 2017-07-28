#include "stdafx.h"
#include "IsoMatrix.h"
#include "Scene.h"


IsoMatrix::IsoMatrix(LPDIRECT3DDEVICE9 device)
	: device(device)
{
}


IsoMatrix::~IsoMatrix()
{
}

void IsoMatrix::Initialize()
{
	tileMap[TILE_COUNT_X][TILE_COUNT_Y] = 0;
	memset(tileMap, 0, sizeof(tileMap));

	isoX = 0;
	isoY = 0;
	corner = 0;


	HRESULT hr;
	hr = D3DXCreateLine(device, &line);
	assert(SUCCEEDED(hr));

}

void IsoMatrix::Destroy()
{
	SAFE_RELEASE(line);
}

void IsoMatrix::Update()
{
	if (Mouse::GetInstance()->ButtonDown(0)) {
		float cellX = (float)(Mouse::GetInstance()->GetPosition().x - INIT_X);
		if (cellX < 0) {
			cellX = (cellX - CELL_WIDTH) / (float)CELL_WIDTH;
		}
		else {
			cellX = cellX / (float)CELL_WIDTH;
		}
		int cellY = abs(Mouse::GetInstance()->GetPosition().y - INIT_Y) / CELL_HEIGHT;

		cellY = (Mouse::GetInstance()->GetPosition().y < INIT_Y) ? cellY* -1 : cellY;

		isoX = (int)cellX + (int)cellY;
		isoY = (int)cellY - (int)cellX;

		if (isoX >= 0 && isoY < TILE_COUNT_X &&
			isoY >= 0 && isoX < TILE_COUNT_Y) {
			corner = GetCurrentIndex(isoX, isoY);

			if (IsInRhombus(corner, isoX, isoY)) {
				corner = 0;
			}
			switch (corner)
			{
			case 1:
				isoX = isoX - 1;
				break;
			case 2:
				isoY = isoY - 1;
				break;
			case 3:
				isoY = isoY + 1;
				break;
			case 4:
				isoX = isoX + 1;
				break;
			}
			tileMap[isoX][isoY] = 1;
		}
	}
}

void IsoMatrix::Render()
{
	DrawTileMap();

	wsprintf(str, L"corner: %d, isoX: %d, isoY: %d", corner, isoX, isoY);

	PrintText::GetInstance()->SetCoord({ 900, 20 });
	PrintText::GetInstance()->AddText(str);
	PrintText::GetInstance()->Render();
}

void IsoMatrix::DrawTileMap()
{
	D3DVIEWPORT9 viewport;
	device->GetViewport(&viewport);

	D3DXMATRIX ortho;
	D3DXMatrixOrthoOffCenterLH(&ortho, 0, viewport.Width, viewport.Height, 0, 0, 1);

	for (int i = 0; i < TILE_COUNT_X; i++) {
		for (int j = 0; j < TILE_COUNT_Y; j++) {
			if (tileMap[i][j] == 1) {
				color = 0xFFFF0000;
				line->SetWidth(2);
			}
			else {
				color = 0xFF000000;
				line->SetWidth(1);
			}
			int left = INIT_X + (i * RADIUS_WIDTH) - (j * RADIUS_WIDTH);
			int top = INIT_Y + (i * RADIUS_HEIGHT) + (j * RADIUS_HEIGHT);

			int centerX = left + RADIUS_WIDTH;
			int centerY = top + RADIUS_HEIGHT;

			DrawRhombus(left, top);
			line->Begin();
			line->DrawTransform(linVector, 5, &ortho, color);
			line->End();
			wsprintf(str, L"(%d, %d)", i, j);

			PrintText::GetInstance()->SetCoord({ centerX, centerY });
			PrintText::GetInstance()->AddText(str);
			PrintText::GetInstance()->Render();
		}
	}
}

void IsoMatrix::DrawRhombus(int left, int top)
{
	int centerX = left + RADIUS_WIDTH;
	int centerY = top + RADIUS_HEIGHT;

	linVector[0] = { (float)centerX, (float)centerY - RADIUS_HEIGHT, 0 };
	linVector[1] = { (float)centerX + RADIUS_WIDTH, (float)centerY, 0 };
	linVector[2] = { (float)centerX, (float)centerY + RADIUS_HEIGHT, 0 };
	linVector[3] = { (float)centerX - RADIUS_WIDTH, (float)centerY, 0 };
	linVector[4] = { (float)centerX, (float)centerY - RADIUS_HEIGHT, 0 };
}

int IsoMatrix::GetCurrentIndex(int isoX, int isoY)
{
	int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
	int top = INIT_Y + (isoX  * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);

	int right = left + CELL_WIDTH;
	int bottom = top + CELL_HEIGHT;

	float dx = (Mouse::GetInstance()->GetPosition().x - left) / (float)CELL_WIDTH;
	float dy = (Mouse::GetInstance()->GetPosition().y - top) / (float)CELL_HEIGHT;

	if (dx < 0.5f && dy < 0.5f) return 1;
	 if (dx > 0.5f && dy < 0.5f) return 2;
	 if (dx < 0.5f && dy > 0.5f) return 3;
	 if (dx > 0.5f && dy > 0.5f) return 4;

	return 0;
}

bool IsoMatrix::IsInRhombus(int corner, int isoX, int isoY)
{
	if (corner == 1) {
		int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
		int top = INIT_Y + (isoX  * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);

		float dx = (float)(Mouse::GetInstance()->GetPosition().x - left) / (CELL_WIDTH) / 2;
		float dy = (float)(Mouse::GetInstance()->GetPosition().y - top) / (CELL_HEIGHT) / 2;

		if ((1.0f - dy) <= dx)
			return true;
		else
			return false;
	}
	else if (corner == 4) {
		int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
		int top = INIT_Y + (isoX  * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);

		left += RADIUS_WIDTH;
		top += RADIUS_HEIGHT;

		float dx = (float)(Mouse::GetInstance()->GetPosition().x - left) / (CELL_WIDTH) / 2;
		float dy = (float)(Mouse::GetInstance()->GetPosition().y - top) / (CELL_HEIGHT) / 2;

		if ((1.0f - dy) >= dx)
			return true;
		else
			return false;
	}
	else if (corner == 2) {
		int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
		int top = INIT_Y + (isoX  * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);

		left += RADIUS_WIDTH;

		float dx = (float)(Mouse::GetInstance()->GetPosition().x - left) / (CELL_WIDTH) / 2;
		float dy = (float)(Mouse::GetInstance()->GetPosition().y - top) / (CELL_HEIGHT) / 2;

		if (dy >= dx)
			return true;
		else
			return false;
	}
	else if (corner == 3) {
		int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
		int top = INIT_Y + (isoX  * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);

		top += RADIUS_HEIGHT;

		float dx = (float)(Mouse::GetInstance()->GetPosition().x - left) / (CELL_WIDTH) / 2;
		float dy = (float)(Mouse::GetInstance()->GetPosition().y - top) / (CELL_HEIGHT) / 2;

		if (dy <= dx)
			return true;
		else
			return false;
	}

}
