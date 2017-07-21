#include "stdafx.h"
#include "Bullet.h"
#include "Sprite.h"
#include "BulletManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Rect.h"

Bullet::Bullet(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 coord, float angle, float speed, float removeSec)
	: device(device)
	, coord(coord)
	, isOn(false)
	, rotation(angle)
	, speed(speed)
	, removeSec(removeSec)
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

	rect = new Rect(device, coord, sprite->GetSize());
	rect->Initialize();
}

void Bullet::Destroy()
{
	rect->Destroy();
	SAFE_DELETE(rect);

	sprite->Destroy();
	SAFE_DELETE(sprite);
}

void Bullet::Update()
{
	coord.x += (int)velocity.x;
	coord.y += (int)velocity.y;

	sprite->SetCoord(coord);
	rect->SetCoord(coord);

	sprite->Update();

	D3DVIEWPORT9 viewport;
	device->GetViewport(&viewport);

	if ((coord.x > viewport.Width && isOn == true)
		|| (coord.x < 0 && isOn == true))
	{
		SetOff();
	}

	DWORD currentTime = timeGetTime();
	if ((currentTime - time) > (removeSec* 1000) 
		&& isOn == false) {
		BulletManager::GetInstance()->Remove(this);
	}
}

void Bullet::Render()
{
	sprite->Render();
}