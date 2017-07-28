#pragma once
#include "TileNode.h"
class Animation;
class TankMap
{
private:
	Animation* _animation;
	tagTile _tiles[TILEX * TILEY];

	DWORD _attribute[TILEX * TILEY];
	int _pos[2];

	LPDIRECT3DDEVICE9 device;
public:
	TankMap(LPDIRECT3DDEVICE9 device);
	~TankMap();

	void initialize();
	void release();
	void update();
	void render();

	void load();

	tagTile* getTiles() { return _tiles; }
	int getPosFirst() { return 0; }
	//int getPosSecond() { return _pos[1]; }

	DWORD* getAttribute() { return _attribute; }
};

