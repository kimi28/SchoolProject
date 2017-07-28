#pragma once

#define CELL_WIDTH 100
#define CELL_HEIGHT 50

#define RADIUS_WIDTH CELL_WIDTH / 2
#define RADIUS_HEIGHT CELL_HEIGHT / 2

#define INIT_X 700
#define INIT_Y 20

#define TILE_COUNT_X 15
#define TILE_COUNT_Y 15

class IsoMatrix : public Scene
{
public:
	IsoMatrix(LPDIRECT3DDEVICE9 device);
	~IsoMatrix();

	void Initialize();
	void Destroy();
	void Update();
	void Render();

	void DrawTileMap();
	void DrawRhombus(int left, int top);
	int GetCurrentIndex(int isoX, int isoY);
	bool IsInRhombus(int corner, int isoX, int isoY);

private:
	LPDIRECT3DDEVICE9 device;
	LPD3DXLINE line;
	DWORD color;
	D3DXVECTOR3 linVector[5];

	int tileMap[TILE_COUNT_X][TILE_COUNT_Y];
	int isoX;
	int isoY;
	int corner;

	WCHAR str[256];
};

