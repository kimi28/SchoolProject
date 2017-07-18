#include "stdafx.h"
#include "GameMain.h"
#include "Sprite.h"
#include "Animation.h"
#include "Rect.h"
#include "Intersect.h"


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

	sprite = new Sprite(device, L"Textures/tilemap.bmp", { (FLOAT)viewport.Width - (FLOAT)TILESIZEX, 0 });
	sprite->Initialize();

	for (int i = 0; i < TILEX * TILEY; i++) {
		tiles[i].animation = new Animation(device, L"Textures/tilemap.bmp", { 20, 8 },
		{ (FLOAT)((i / TILEX) * TILESIZE), (FLOAT)((i % TILEY) * TILESIZE) });
	}
	MapToolSetup();
}

void GameMain::Destroy()
{
	for (int i = 0; i < TILEX* TILEY; i++) {
		SAFE_DELETE(tiles[i].animation);
	}
	for (int i = 0; i < SAMPLETILEY; i++) {
		for (int j = 0; i < SAMPLETILEX; j++) {
			SAFE_DELETE(sampleTiles[i].rcTile);
		}
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
	device->GetViewport(&viewport);

	ctrSelect = CTRL_TERRAINDRAW;

	for (int i = 0; i < SAMPLETILEY; i++) {
		for (int j = 0; j < SAMPLETILEX; j++) {
			sampleTiles[i*SAMPLETILEX + j].terrainFrameX = j;
			sampleTiles[i*SAMPLETILEX + j].terrainFrameY = i;

			sampleTiles[i*SAMPLETILEX + j].rcTile = new Rect(device,
			{ (FLOAT)(viewport.Width - SAMPLETILEX * TILESIZE) + j * TILESIZE, (FLOAT)(TILESIZE* i) },
			{ (FLOAT)TILESIZE, (FLOAT)TILESIZE });
		}
	}

	for (int i = 0; i < TILEX* TILEY; i++) {
		tiles[i].terrainFrameX = 2;
		tiles[i].terrainFrameY = 0;
		tiles[i].objFrameX = 0;
		tiles[i].objFrameY = 0;
		tiles[i].terrain = TerrainSelect(tiles[i].terrainFrameX, tiles[i].terrainFrameY);
		tiles[i].obj = OBJ_NONE;
		tiles[i].animation->Update({ tiles[i].terrainFrameX, tiles[i].terrainFrameY });
	}
}

void GameMain::SetMap()
{
	for (int i = 0; i < SAMPLETILEX* SAMPLETILEY; i++) {
		if (Intersect::IsPointInRect(&Mouse::GetInstance()->GetPosition(), sampleTiles[i].rcTile)) {
			if (Mouse::GetInstance()->ButtonDown(0)) {
				currentTile.x = sampleTiles[i].terrainFrameX;
				currentTile.y = sampleTiles[i].terrainFrameY;
				break;
			}
		}
	}
	for (int i = 0; i < TILEX* TILEY; i++) {
		if (Intersect::IsPointInRect(&Mouse::GetInstance()->GetPosition(), tiles[i].animation->GetRect())) {
			if (Mouse::GetInstance()->ButtonPress(0)) {
				if (ctrSelect == CTRL_TERRAINDRAW) {
					tiles[i].terrainFrameX = currentTile.x;
					tiles[i].terrainFrameY = currentTile.y;

					tiles[i].terrain = TerrainSelect(tiles[i].terrainFrameX, tiles[i].terrainFrameY);
					tiles[i].animation->Update({ tiles[i].terrainFrameX, tiles[i].terrainFrameY });
				}
				else if (ctrSelect == CTRL_OBJDRAW) {
					tiles[i].objFrameX = currentTile.x;
					tiles[i].objFrameY = currentTile.y;

					tiles[i].obj = ObjSelect(tiles[i].objFrameX, tiles[i].objFrameY);
					tiles[i].animation->Update({ tiles[i].objFrameX, tiles[i].objFrameY });
				}
				else if (ctrSelect == CTRL_ERASER) {
					tiles[i].objFrameX = 0;
					tiles[i].objFrameY = 0;

					tiles[i].obj = OBJ_NONE;
					tiles[i].terrain = TR_END;
				}
			}
		}
	}
}

void GameMain::Save()
{

}

void GameMain::Load()
{

}

TERRAIN GameMain::TerrainSelect(int frameX, int frameY)
{
	if (frameX == 1 && frameY == 0) {
		return TR_CEMENT;
	}
	if (frameX = 2 && frameY == 0) {
		return TR_GROUND;
	}
	if (frameX == 3 && frameY == 0) {
		return TR_GRASS;
	}
	if (frameX == 4 && frameY == 0) {
		return TR_WATER;
	}

	return TR_GRASS;
}

OBJECT GameMain::ObjSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0) {
		return OBJ_TANK1;
	}
	if (frameX == 19 && frameY == 7) {
		return OBJ_TANK2;
	}
	if (frameX == 0 && frameY == 1) {
		return OBJ_BLOCK1;
	}
	if (frameX == 17 && frameY == 2) {
		return OBJ_BLOCK2;
	}
	if (frameX == 12 && frameY == 3) {
		return OBJ_BLOCK3;
	}

	return OBJ_BLOCK1;
}
