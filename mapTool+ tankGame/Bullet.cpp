#include "stdafx.h"
#include "Bullet.h"
#include "Sprite.h"
#include "Rect.h"

Bullet::Bullet(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 coord,
	float angle, float speed)
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
	sprite = new Sprite(device, L"Textures/eplasma.tga", coord);
	sprite->Initialize();
	coord.y -= sprite->GetRealSize().y * 0.5f;
	sprite->SetCoord(coord);

	sprite2 = new Sprite(device, L"Textures/eplasma2.tga", coord);
	sprite2->Initialize();

	rect = new Rect(device, coord, sprite->GetSize());
}

void Bullet::Destroy()
{
	sprite->Destory();
	SAFE_DELETE(sprite);

	sprite2->Destory();
	SAFE_DELETE(sprite2);

	rect->Destroy();
	SAFE_DELETE(rect);
}

void Bullet::Update()
{
	coord.x += velocity.x;
	coord.y += velocity.y;

	sprite->SetCoord(coord);
	sprite2->SetCoord(coord);
	
	D3DVIEWPORT9 viewport;
	device->GetViewport(&viewport);

	if (coord.x > viewport.Width)
	{
		isOn = false;

		//time = timeGetTime();
	}

	DWORD currentTime = timeGetTime();
	if (currentTime - time > 5000)
	{
		//BulletManager::GetInstance()->Remove(this);
	}
	rect->SetCoord(coord);
}

void Bullet::Render(int bulletNum)
{
	if (bulletNum == 0)
		sprite->Render();
	else
		sprite2->Render();
}
