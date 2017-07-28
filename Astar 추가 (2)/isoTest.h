#pragma once

#define CELL_WIDTH	100	//타일 가로크기
#define CELL_HEIGHT 50	//세로크기

#define RADIUS_WIDTH	CELL_WIDTH / 2
#define RADIUS_HEIGHT	CELL_HEIGHT / 2

#define INIT_X	700	//초기화 좌표
#define INIT_Y	20	

#define TILE_COUNT_X 15	//타일 갯수
#define TILE_COUNT_Y 15	//타일 갯수


class isoTest : public Scene
{
private:
	int _tileMap[TILE_COUNT_X][TILE_COUNT_Y];
	int _isoX, _isoY;
	int _corner;
	WCHAR str[128];

	LPD3DXLINE line;
	DWORD lineColor;
	D3DXVECTOR3 lineVector[5];
	LPDIRECT3DDEVICE9 device;


public:
	isoTest(LPDIRECT3DDEVICE9 device);
	~isoTest();

	void Initialize();
	void Update();
	void Destroy();
	void Render();

	//타일맵 그려주는 함수
	void drawTileMap();
	//마름모 그려주는 함수
	void drawRhombus(int left, int top);
	//코너 검출(1~4분면)
	int getCornerIndex(int isoX, int isoY);
	//코너 안에 있는지 검출
	bool isInRhombus(int corner, int isoX, int isoY);
};

