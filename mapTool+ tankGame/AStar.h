#pragma once

#define TILE_X 20
#define TILE_Y 20
#define WIDTH 40
#define HEIGHT 40
#define BIGNUM 5000

enum TILE_TYPE
{
	TILE_TYPE_EMPTY,
	TILE_TYPE_START,
	TILE_TYPE_END,
	TILE_TYPE_WALL
};

enum ASTAR_STARE
{
	ASTAR_STATE_SEARCHING,
	ASTAR_STATE_FOUND,
	ASTAR_STATE_NOWAY,
	ASTAR_STATE_END
};

typedef struct tagMYVERTEX {
	D3DXVECTOR3 pos;
	DWORD color;
	enum{FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE};
}MYVERTEX, *LPMYVERTEX;

struct aStarTile {
	MYVERTEX vertices[4];
	bool walkable;
	bool listOn;
	int i, j;
	int F, G, H;
	WCHAR str[128];
	aStarTile* parent;
	TILE_TYPE type;
};

class Rect;
class AStar : public Scene
{
public:
	AStar(LPDIRECT3DDEVICE9 device);
	~AStar();

	void Initialize();
	void Destroy();
	void Update();
	void Render();

	void TileComposition();
	void TileInitializing();
	void AddOpenList();
	void CalculateH();
	void CalculateF();
	void AddCloseList();
	void CheckArrive();
	void ShowWay(aStarTile* tile);

private:
	LPDIRECT3DDEVICE9 device;

	Rect* rect;
	aStarTile tile[TILE_X][TILE_Y];
	vector<aStarTile*> openList;
	vector<aStarTile*> closeList;

	ASTAR_STARE aStarState;
	TILE_TYPE selectedType;

	DWORD selectedTypeColor;

	int startX, startY;
	int endX, endY;
	int lastIndex;

	bool startPointSet;
	bool endPointSet;

	int Ci;
	int Cj;
	int Cg;
};

