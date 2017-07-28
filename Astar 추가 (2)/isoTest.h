#pragma once

#define CELL_WIDTH	100	//Ÿ�� ����ũ��
#define CELL_HEIGHT 50	//����ũ��

#define RADIUS_WIDTH	CELL_WIDTH / 2
#define RADIUS_HEIGHT	CELL_HEIGHT / 2

#define INIT_X	700	//�ʱ�ȭ ��ǥ
#define INIT_Y	20	

#define TILE_COUNT_X 15	//Ÿ�� ����
#define TILE_COUNT_Y 15	//Ÿ�� ����


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

	//Ÿ�ϸ� �׷��ִ� �Լ�
	void drawTileMap();
	//������ �׷��ִ� �Լ�
	void drawRhombus(int left, int top);
	//�ڳ� ����(1~4�и�)
	int getCornerIndex(int isoX, int isoY);
	//�ڳ� �ȿ� �ִ��� ����
	bool isInRhombus(int corner, int isoX, int isoY);
};

