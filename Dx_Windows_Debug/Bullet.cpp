#include "stdafx.h"
#include "Bullet.h"
#include "Circle.h"



Bullet::Bullet(LPDIRECT3DDEVICE9 device, POINT coord)
	: device(device)
	, coord(coord)

{
	Initialize();
}


Bullet::~Bullet()
{
	Destroy();
}

void Bullet::Initialize()
{
	circle = new Circle(device, coord, 3, 5, 0xFFFF0000);
	circle->Initalize();
}

void Bullet::Destroy()
{
	circle->Destroy();
	SAFE_DELETE(circle);
}

void Bullet::Update()
{
	coord.x += 8;
	circle->SetCoord(coord);
	circle->Update();
}

void Bullet::Render()
{
	circle->Render();
}
