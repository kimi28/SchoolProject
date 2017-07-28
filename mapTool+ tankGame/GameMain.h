#pragma once
#include "DxWindow.h"
//ȭ�����

class Animation;
class Sprite;
class Rect;
#define TILESIZE 32
#define TILEX 20
#define TILEY 20
#define TILESIZEX TILEX * TILESIZE
#define TILESIZEY TILEY * TILESIZE

//ȭ�� ������ �̹��� Ÿ�� ����
#define SAMPLETILEX 20
#define SAMPLETILEY 8

//����

enum CTRL
{
	CTRL_SAVE,
	CTRL_LOAD,
	CTRL_TERRAINDRAW,
	CTRL_OBJDRAW,
	CTRL_ERASER,
	CTRL_MAP1,
	CTRL_MAP2,
	CTRL_END
};
enum TERRAIN
{
	TR_CEMENT,
	TR_GROUND,
	TR_GRASS,
	TR_WATER,
	TR_END
};

//������Ʈ
enum OBJECT
{
	OBJ_BLOCK1,
	OBJ_BLOCK2,
	OBJ_BLOCK3,
	OBJ_TANK1,
	OBJ_TANK2,
	OBJ_FLAG1,
	OBJ_FLAG2,
	OBJ_NONE
};

//��ġ��ǥ
enum POS
{
	POS_FLAG1,
	POS_FLAG2,
	POS_TANK1,
	POS_TANK2
};

//Ÿ�ϱ���ü
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	Rect* rc;

	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
};

//�̹��� Ÿ�� ����ü
struct tagSampleTile
{
	Rect* rcTile;
	int terrainFrameX;
	int terrainFrameY;
};

struct tagCurrentTile
{
	int x;
	int y;
};



class GameMain : public DxWindow
{
public:
	GameMain(HINSTANCE hInstance, LPCWSTR className, LPCSTR lpCmdLine, int nCmdShow);
	~GameMain();

	void Initialize();
	void Destroy();
	void Update();
	void Render();
	
	//���� ����
	void maptoolSetup();
	void setMap();

	//����
	void save();
	void load();

	//����,������Ʈ
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objSelect(int frameX, int frameY);
private:
	Animation* _animation;
	Sprite* _sprite;
	Rect* rcTile;

	tagCurrentTile m_currentTile;
	tagTile m_tiles[TILEX * TILEY];
	tagSampleTile m_sampleTile[SAMPLETILEX * SAMPLETILEY];
	int m_pos[2];
	int ctrSelect;


};

