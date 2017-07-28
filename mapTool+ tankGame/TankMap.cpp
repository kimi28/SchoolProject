#include "stdafx.h"
#include "TankMap.h"
#include "Animation.h"
#include "Rect.h"



TankMap::TankMap(LPDIRECT3DDEVICE9 device)
	:device(device)
{
	initialize();
}


TankMap::~TankMap()
{
}

void TankMap::initialize()
{
	_animation = new Animation(device, L"Textures/tilemap.bmp", { SAMPLETILEX,SAMPLETILEY });

	this->load();
}

void TankMap::release()
{
}

void TankMap::update()
{
}

void TankMap::render()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_animation->SetCoord({ _tiles[i].rc->GetCoord() });
		_animation->Update({ _tiles[i].terrainFrameX, _tiles[i].terrainFrameY });
		_animation->Render();
		if (_tiles[i].obj == OBJ_NONE) continue;

		_animation->SetCoord({ _tiles[i].rc->GetCoord() });
		_animation->Update({ _tiles[i].objFrameX, _tiles[i].objFrameY });
		_animation->Render();
		_tiles[i].rc->Render();
	}
}

void TankMap::load()
{
	HANDLE file;
	DWORD read;
	file = CreateFile(L"tileMap.map",
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	ReadFile(file, _pos, sizeof(int) * 2, &read, NULL);
	CloseHandle(file);
	memset(_attribute, 0, sizeof(DWORD) * TILEX * TILEY);

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_tiles[i].rc =
			new Rect(device, { (float)(i % TILEX * TILESIZE),
			(float)(i / TILEY * TILESIZE) }, { (float)TILESIZE,(float)TILESIZE });
		_tiles[i].rc->Initialize();
		if (_tiles[i].obj == OBJ_TANK1 || _tiles[i].obj == OBJ_TANK2)
		{
			_tiles[i].obj = OBJ_NONE;
		}


		if (_tiles[i].terrain == TR_WATER) 
			_attribute[i] = ATTR_UNMOVE;
		if (_tiles[i].obj == OBJ_BLOCK1) 
			_attribute[i] = ATTR_UNMOVE;
		if (_tiles[i].obj == OBJ_BLOCK2) 
			_attribute[i] = ATTR_UNMOVE;

	}
}
