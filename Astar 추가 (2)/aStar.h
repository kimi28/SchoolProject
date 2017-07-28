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
enum ASTAR_STATE
{
	ASTAR_STATE_SEARCHING,
	ASTAR_STATE_FOUND,
	ASTAR_STATE_NOWAY,
	ASTAR_STATE_END
};
//정점하나에 대한 정보를 정의하는 구조체
typedef struct tagMYVERTEX {
	D3DXVECTOR3 pos;			//정점의 위치
	DWORD		color;			//정점의 컬러

								//현제 정점의 정보를 나타내는 플래그 상수값 
	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
	//D3DFVF_XYZ 정점의 위치정보 | D3DFVF_DIFFUSE 정점의 컬러정보
	// FVF 의 선언 순서에 따라 구조체 자료형도 순서대로 해주어야 한다.
}MYVERTEX, *LPMYVERTEX;
struct aStarTile
{
	MYVERTEX vertices[4];	//정점 구조체 3개	
	bool walkable;
	bool liston;
	int i, j;
	int F, G, H;
	WCHAR str[128];
	aStarTile* parent;
	TILE_TYPE type;
};
class Rect;
class aStar : public Scene
{
public:
	aStar(LPDIRECT3DDEVICE9 device);
	~aStar();

	void Initialize();
	void Destroy() ;
	void Update() ;
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
	aStarTile _tile[TILE_X][TILE_Y];
	vector<aStarTile*> _openList;
	vector<aStarTile*> _closeList;

	ASTAR_STATE _aStarState;
	TILE_TYPE _selectedType;

	DWORD _selectedTypeColor;
	int _startX, _startY;
	int _endX, _endY;
	int _lastIndex;

	bool _startPointSet;
	bool _endPointSet;
	int Ci;
	int Cj;
	int Cg;

};

