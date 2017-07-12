#pragma once
#include "DxWindow.h"

class Sprite;
class Rect;
class Animation;

enum CTRL {
	CTRL_SAVE,
	CTRL_LOAD,
	CTRL_TERRAINDRAW,
	CTRL_OBJDRAW,
	CTRL_ERASER,
	CTRL_MAP1,
	CTRL_MAP2,
	CTRL_END
};

#define	TILESIZE 32
#define TILEX 20
#define TILEY 20
#define TILESIZEX TILEX *TILESIZE
#define TILESIZEY TILEY *TILESIZE

#define SAMPLETILEX 20
#define SAMPLETILEY 8

enum TERRAIN {
	TR_CEMENT,
	TR_GROUND,
	TR_GRASS,
	TR_WATER,
	TR_END
};

enum OBJECT {
	OBJ_BLOCK1,
	OBJ_BLOCK2,
	OBJ_BLOCK3,
	OBJ_TANK1,
	OBJ_TANK2,
	OBJ_FLAG1,
	OBJ_FLAG2,
	OBJ_NONE
};

enum POS {
	POS_FALG1,
	POS_FALG2,
	POS_TANK1,
	POS_TANK2
};

struct tagTile
{
	Animation *animation;
	TERRAIN terrain;
	OBJECT obj;
	Rect* rect;

	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
};

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

	void MapToolSetup();
	void SetMap();
	
	void Save();
	void Load();

	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT ObjSelect(int frameX, int frameY);

private:
	Sprite* sprite;

	int ctrSelect;
	tagCurrentTile currentTile;
	tagTile tiles[TILEX * TILEY];
	tagSampleTile sampleTiles[SAMPLETILEX * SAMPLETILEY];
	int pos[2];

	D3DVIEWPORT9 viewport;
};