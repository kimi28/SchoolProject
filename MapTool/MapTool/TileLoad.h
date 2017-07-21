#pragma once
#include "Animation.h"
#include "Sprite.h"
#include "Rect.h"

class Sprite;
class Rect;
class Animation;

#define	TILESIZE 32
#define TILEX 20
#define TILEY 20
#define TILESIZEX TILEX *TILESIZE
#define TILESIZEY TILEY *TILESIZE

#define SAMPLETILEX 20
#define SAMPLETILEY 8

#define ATTR_UMMOVE 0x00000001
#define ATTR_POSITION 0x00000002

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
	Animation* animation;
	TERRAIN terrain;
	OBJECT obj;

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

