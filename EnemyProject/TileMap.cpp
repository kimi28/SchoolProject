#include "stdafx.h"
#include "TileMap.h"



TileMap::TileMap(LPDIRECT3DDEVICE9 device)
	:device (device)
{
	this->Initialize();
}


TileMap::~TileMap()
{
}

void TileMap::Initialize()
{
	animation = new Animation(device, L"Textures/tilemap.bmp", { SAMPLETILEX, SAMPLETILEY });
	this->Load();
}

void TileMap::Destroy()
{
	SAFE_DELETE(animation);
	for (int i = 0; i < TILEX*TILEY; i++) {
		SAFE_DELETE(tiles[i].rect);
	}
}

void TileMap::Update()
{
}

void TileMap::Render()
{
	for (int i = 0; i < TILEX*TILEY; i++) {
		animation->SetCoord({ tiles[i].rect->GetCoord() });
		animation->Update({ tiles[i].terrainFrameX,tiles[i].terrainFrameY });

	}

}

void TileMap::Load()
{
	HANDLE file;
	DWORD read;
	tagTile saveTile[TILEX* TILEY];

	file = CreateFile(L"tileMap.map",
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	ReadFile(file, saveTile, sizeof(tagTile)*TILEX* TILEY, &read, NULL);
	ReadFile(file, pos, sizeof(int) * 2, &read, NULL);
	CloseHandle(file);
	memset(attribute, 0, sizeof(DWORD)* TILEX* TILEY);
	for (int i = 0; i < TILEX*TILEY; i++) {
		tiles[i].obj = saveTile[i].obj;
		tiles[i].objFrameX = saveTile[i].objFrameX;
		tiles[i].objFrameY = saveTile[i].objFrameY;
		tiles[i].terrain = saveTile[i].terrain;
		tiles[i].terrainFrameX = saveTile[i].terrainFrameX;
		tiles[i].terrainFrameY = saveTile[i].terrainFrameY;

		if (tiles[i].obj == OBJ_TANK1 || tiles[i].obj == OBJ_TANK2) {
			tiles[i].obj == OBJ_NONE;
		}
		
		

		if (tiles[i].terrain == TR_WATER) attribute[i] = ATTR_UMMOVE;
		if (tiles[i].obj == OBJ_BLOCK1) attribute[i] = ATTR_UMMOVE;
		if (tiles[i].obj == OBJ_BLOCK2) attribute[i] = ATTR_UMMOVE;

		if (tiles[i].obj = OBJ_NONE) {
			tiles[i].animation->Update({ tiles[i].terrainFrameX, tiles[i].terrainFrameY });
		}
		else {
			tiles[i].animation->Update({ tiles[i].objFrameX, tiles[i].objFrameY });
		}
	}
}
