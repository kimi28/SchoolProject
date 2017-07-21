#include "stdafx.h"
#include "Enemy.h"
#include "Sprite.h"
#include "Bullet.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "Rect.h"
#include "Player.h"
#include "Intersect.h"

Enemy::Enemy(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 coord, float angle, float moveSpeed, float removeSec)
	: device(device)
	, coord(coord)
	, moveSpeed(moveSpeed)
	, angle(angle)
	, removeSec(removeSec)
	, isOn(false)
	, bulletSpeed(-5.0f)
{
	Initialize();
}

Enemy::~Enemy()
{
	Destroy();
}

void Enemy::Initialize()
{
	sprite = new Sprite(device, L"Textures/SplitHorizon.tga", coord);
	sprite->Initialize();

	D3DVIEWPORT9 viewport;
	device->GetViewport(&viewport);

	float halfY = viewport.Height * 0.5f;
	float spriteHalfY = sprite->GetRealSize().y * 0.5f;
	coord = D3DXVECTOR2(900, halfY - spriteHalfY);
	sprite->SetCoord(coord);

	sprite->SetRotate(180);

	time = timeGetTime();

	BulletManager::GetInstance()->SetDevice(device);

	rect = new Rect(device, coord, sprite->GetSize());
	rect->Initialize();
}

void Enemy::Destroy()
{
	BulletManager::DeleteInstance();

	rect->Destroy();
	SAFE_DELETE(rect);

	sprite->Destroy();
	SAFE_DELETE(sprite);
}

void Enemy::Update()
{
	coord.x -= moveSpeed;

	sprite->SetCoord(coord);
	rect->SetCoord(coord);
	BulletManager::GetInstance()->SetAngle(angle);
	BulletManager::GetInstance()->SetSpeed(bulletSpeed);

	DWORD currentTime = timeGetTime();
	int random = 500 + rand() % 5 * 100;

	if (currentTime - time > random)
	{
		D3DXVECTOR2 point1 = coord;
		point1.x += 40;
		point1.y += 40;

		BulletManager::GetInstance()->Add(point1);

		D3DXVECTOR2 point2 = coord;
		point2.x += 40;
		point2.y += 15;

		BulletManager::GetInstance()->Add(point2);

		time = timeGetTime();
	}

	D3DVIEWPORT9 viewport;
	device->GetViewport(&viewport);

	if ((coord.x > viewport.Width && isOn == true)
		|| (coord.x < 0 && isOn == true))
	{
		SetOff();
	}

	DWORD currentTime1 = timeGetTime();
	if ((currentTime1 - time) >(removeSec * 1000)
		&& isOn == false) {
		EnemyManager::GetInstance()->Remove(this);
	}

	BulletManager::GetInstance()->Update();

}

void Enemy::Render()
{
	sprite->Render();
	BulletManager::GetInstance()->Render();
}

void Enemy::Collison()
{
}

void Enemy::Remove(Bullet * bullet)
{
	//auto iter = bulletList.begin();
	//for (iter; iter != bulletList.end();) {
	//	if ((*iter) == bullet) {
	//		SAFE_DELETE(bullet);
	//		iter = bulletList.erase(iter);
	//	}
	//	else {
	//		iter++;
	//	}
	//}
}