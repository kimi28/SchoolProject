#include "stdafx.h"
#include "Monster.h"
#include "Rect.h"



Monster::Monster(LPDIRECT3DDEVICE9 device)
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
}

void Monster::Destroy()
{
	rect->Destroy();
	SAFE_DELETE(rect);
}

void Monster::Update()
{
}

void Monster::Render()
{
}
