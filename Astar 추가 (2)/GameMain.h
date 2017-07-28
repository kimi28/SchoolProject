#pragma once
#include "DxWindow.h"
//화면왼쪽

class Animation;
class Sprite;
class Rect;
#define TILESIZE 32
#define TILEX 20
#define TILEY 20
#define TILESIZEX TILEX * TILESIZE
#define TILESIZEY TILEY * TILESIZE

//화면 오른쪽 이미지 타일 갯수
#define SAMPLETILEX 20
#define SAMPLETILEY 8

//지형

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

//오브젝트
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

//위치좌표
enum POS
{
	POS_FLAG1,
	POS_FLAG2,
	POS_TANK1,
	POS_TANK2
};

//타일구조체
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

//이미지 타일 구조체
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
	
	//맵툴 셋팅
	void maptoolSetup();
	void setMap();

	//숙제
	void save();
	void load();

	//지형,오브젝트
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objSelect(int frameX, int frameY);
private:
	//정점하나에 대한 정보를 정의하는 구조체
	typedef struct tagMYVERTEX {
		D3DXVECTOR3 pos;			//정점의 위치
		DWORD		color;			//정점의 컬러

									//현제 정점의 정보를 나타내는 플래그 상수값 
		enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
		//D3DFVF_XYZ 정점의 위치정보 | D3DFVF_DIFFUSE 정점의 컬러정보
		// FVF 의 선언 순서에 따라 구조체 자료형도 순서대로 해주어야 한다.
	}MYVERTEX, *LPMYVERTEX;

	Animation* _animation;
	Sprite* _sprite;
	Rect* rcTile;

	tagCurrentTile m_currentTile;
	tagTile m_tiles[TILEX * TILEY];
	tagSampleTile m_sampleTile[SAMPLETILEX * SAMPLETILEY];
	int m_pos[2];
	int ctrSelect;
	MYVERTEX vertices[3];	//정점 구조체 3개	


};

