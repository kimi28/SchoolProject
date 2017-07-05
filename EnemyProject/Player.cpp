#include "stdafx.h"
#include "Player.h"
#include "Sprite.h"
#include "Bullet.h"
#include "BulletManager.h"
#include "Rect.h"
#include "Enemy.h"
#include "Intersect.h"

Player::Player(LPDIRECT3DDEVICE9 device)
	: device(device)
	, coord(0, 0)
	, moveSpeed(5)
	, angle(0)
	, bulletSpeed(10.0f)
{
	Initialize();
}

Player::~Player()
{
	Destroy();
}

void Player::Initialize()
{
	sprite = new Sprite(device,
		L"Textures/SplitHorizon.tga",
		coord);
	sprite->Initialize();

	D3DVIEWPORT9 viewport;
	device->GetViewport(&viewport);

	float halfY = viewport.Height * 0.5f;
	float spriteHalfY = sprite->GetRealSize().y * 0.5f;
	coord = D3DXVECTOR2(30, halfY - spriteHalfY);
	sprite->SetCoord(coord);

	rect = new Rect(device, D3DXVECTOR2(30, halfY - spriteHalfY), sprite->GetSize());
	rect->Initialize();

	time = timeGetTime();
}

void Player::Destroy()
{
	rect->Destroy();
	SAFE_DELETE(rect);

	sprite->Destroy();
	SAFE_DELETE(sprite);

}

void Player::Update()
{
	if (Keyboard::GetInstance()->KeyPress(VK_UP)) {
		coord.y -= moveSpeed;
	}
	else if (Keyboard::GetInstance()->KeyPress(VK_DOWN)) {
		coord.y += moveSpeed;
	}

	sprite->SetCoord(coord);
	rect->SetCoord(coord);
	BulletManager::GetInstance()->SetAngle(angle);
	BulletManager::GetInstance()->SetSpeed(bulletSpeed);


	if (Keyboard::GetInstance()->KeyDown(VK_SPACE)) {
		D3DXVECTOR2 point1 = coord;
		point1.x += 40;
		point1.y += 40;

		BulletManager::GetInstance()->Add(point1);


		D3DXVECTOR2 point2 = coord;
		point2.x += 40;
		point2.y += 15;

		BulletManager::GetInstance()->Add(point2);
	}
	
}

void Player::Render()
{
	sprite->Render();
}

void Player::Collison()
{
}
