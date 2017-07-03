#include "stdafx.h"
#include "Bullet.h"
#include "Sprite.h"
#include "Player.h"
#include "Enemy.h"

Bullet::Bullet(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 coord, float angle, float speed)
	: device(device)
	, coord(coord)
	, isOn(false)
	, rotation(angle)
	, speed(speed)
{
	Initialize();

	SetRotate(angle);
}

Bullet::~Bullet()
{
	Destroy();
}

void Bullet::SetRotate(float angle)
{
	rotation = angle;

	velocity = D3DXVECTOR2();
	velocity.x = (float)cos(D3DXToRadian(angle));
	velocity.y = (float)sin(D3DXToRadian(angle));
	velocity *= speed;
}

void Bullet::Initialize()
{
	sprite = new Sprite(device, L"Textures/eplasma2.tga", coord);
	sprite->Initialize();
}

void Bullet::Destroy()
{
	sprite->Destroy();
	SAFE_DELETE(sprite);
}

void Bullet::Update()
{
	coord.x += (int)velocity.x;
	coord.y += (int)velocity.y;

	sprite->SetCoord(coord);

	D3DVIEWPORT9 viewport;
	device->GetViewport(&viewport);

	if ((coord.x > viewport.Width && isOn == true)  || (coord.x < 0 && isOn == true))
	{

		//isOn = false;
		SetOff();

	}

	DWORD currentTime = timeGetTime();
	if ((currentTime - time) > 5000) {

	}
}

void Bullet::Render()
{
	sprite->Render();
}