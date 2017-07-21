#pragma once
#include "TileLoad.h"

class TileMap
{

public:
	TileMap(LPDIRECT3DDEVICE9 device);
	~TileMap();
	void Initialize();
	void Destroy();
	void Update();
	void Render();

	void Load();

	tagTile* GetTiles() { return tiles; }
	int GetPosFirst() {return 0;}

	DWORD* GetAttribute() { return attribute; }

private:
	Animation* animation;
	tagTile tiles[TILEX * TILEY];
	DWORD attribute[TILEX* TILEY];

	int pos[2];

	LPDIRECT3DDEVICE9 device;
};

