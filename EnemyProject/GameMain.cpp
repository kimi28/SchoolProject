#include "stdafx.h"
#include "GameMain.h"
#include "Sprite.h"
#include "Animation.h"
#include "Rect.h"


GameMain::GameMain(HINSTANCE hInstance, LPCWSTR className, LPCSTR lpCmdLine, int nCmdShow)
	: DxWindow(hInstance, className, lpCmdLine, nCmdShow)
{
}

GameMain::~GameMain()
{
}

void GameMain::Initialize()
{
	currentTile.x = 2;
	currentTile.y = 0;
	device->GetViewport(&viewport);

	sprite = new Sprite(device, L"Textures/tilemap.bmp", { (FLOAT)viewport.Width - (FLOAT)TILESIZE, 0 });
	sprite->Initialize();

	for (int i = 0; i < TILEX * TILEY; i++) {
		tiles[i].animation = new Animation(device, L"Textures/tilemap.bmp", { 20, 8 },
		{ (FLOAT)(i / TILEX * TILESIZE), (FLOAT)(i %TILEY * TILESIZE) });

		MapToolSetup();
	}
}

void GameMain::Destroy()
{
	for (int i = 0; i < TILEX* TILEY; i++) {
		SAFE_DELETE(tiles[i].animation);
		SAFE_DELETE(tiles[i].rect);
	}
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++) {
		SAFE_DELETE(sampleTiles[i].rcTile);
	}
}

void GameMain::Update()
{
	SetMap();
}

void GameMain::Render()
{
	sprite->Render();
	for (int i = 0; i < TILEX* TILEY; i++) {
		tiles[i].animation->Render();
	}
}

void GameMain::MapToolSetup()
{
}

void GameMain::SetMap()
{
}

void GameMain::Save()
{
}

void GameMain::Load()
{
}

TERRAIN GameMain::terrainSelect(int frameX, int frameY)
{
	return TERRAIN();
}

OBJECT GameMain::ObjSelect(int frameX, int frameY)
{
	return OBJECT();
}
