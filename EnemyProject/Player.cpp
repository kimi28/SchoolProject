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
{
}

Player::~Player()
{
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
	for (size_t i = 0; i < bulletList.size(); i++) {
		SAFE_DELETE(bulletList[i]);
	}
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
	Collison();

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



	for (size_t i = 0; i < bulletList.size(); i++) {
		bulletList[i]->Update();
	}


}

void Player::Render()
{

	sprite->Render();
}

void Player::Collison()
{
	for (size_t i = 0; i < bulletList.size(); i++) {
		if (Intersect::IsContainRect(NULL, bulletList[i]->GetRect(), enemyMemoryLink->GetRect())) {
			Remove(bulletList[i]);
			Remove(enemyMemoryLink);
		}
	}
}

void Player::Remove(Enemy * enemy)
{

}

void Player::Remove(Bullet * bullet)
{
	auto iter = bulletList.begin();
	for (iter; iter != bulletList.end();) {
		if ((*iter) == bullet) {
			SAFE_DELETE(bullet);
			iter = bulletList.erase(iter);
		}
		else {
			iter++;
		}
	}
}