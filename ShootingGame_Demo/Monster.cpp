#include "stdafx.h"
#include "Monster.h"
#include "Rect.h"



Monster::Monster(LPDIRECT3DDEVICE9 device, POINT coord)
	: device(device)
	, coord(coord)
{
	Initialize();
}


Monster::~Monster()
{
	Destroy();
}

void Monster::Initialize()
{
	rect = new Rect(device, coord, { 40,40 }, 0xFF00FF00);
	rect->Initialize();

	rectList.push_back(rect);
}

void Monster::Destroy()
{
	rect->Destroy();
	SAFE_DELETE(rect);
}

void Monster::Update()
{
	if (rectList.size() != NULL) {
		rectList.push_back(rect);
	}



}

void Monster::Render()
{
}
