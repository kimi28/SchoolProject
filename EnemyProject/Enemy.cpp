#include "stdafx.h"
#include "Enemy.h"
#include "Sprite.h"
#include "Bullet.h"

Enemy::Enemy(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 coord)
	: device(device)
	, coord(coord)
	, moveSpeed(5)
	, angle(0)
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
	coord = D3DXVECTOR2(950, halfY - spriteHalfY);
	sprite->SetCoord(coord);

	sprite->SetRotate(180);

	time = timeGetTime();
}

void Enemy::Destroy()
{
	for (size_t i = 0; i < bulletList.size(); i++) {
		SAFE_DELETE(bulletList[i]);
	}

	sprite->Destroy();
	SAFE_DELETE(sprite);

}

void Enemy::Update()
{
	coord.x -= moveSpeed;
	sprite->SetCoord(coord);

	DWORD currentTime = timeGetTime();
	int random = 500 + rand() % 5 * 100;

	if (currentTime - time > random)
	{

		D3DXVECTOR2 point1 = coord;
		point1.x += 40;
		point1.y += 40;

		Add(point1);


		D3DXVECTOR2 point2 = coord;
		point2.x += 40;
		point2.y += 15;

		Add(point2);


		time = timeGetTime();
	}

	for (size_t i = 0; i < bulletList.size(); i++) {
		bulletList[i]->Update();
	}
}

void Enemy::Render()
{
	for (size_t i = 0; i < bulletList.size(); i++) {
		bulletList[i]->Render();
	}
	sprite->Render();
}

void Enemy::Add(D3DXVECTOR2 coord)
{
	int number = -1;
	for (size_t i = 0; i < bulletList.size(); i++) {
		if (bulletList[i]->GetIsOn() == false) {
			number = (int)i;
			break;
		}
	}

	if (number > -1) {
		bulletList[number]->SetOn();
		bulletList[number]->SetCoord(coord);
		bulletList[number]->SetRotate(angle);
	}
	else {
		Bullet* bullet = new Bullet(device, coord, angle, -10.0f);
		bullet->SetOn();
		bulletList.push_back(bullet);
	}
}

void Enemy::Remove(Bullet * bullet)
{
	for (vector<Bullet*>::iterator iter = bulletList.begin();
		iter != bulletList.end();) {
		if ((*iter) == bullet) {
			SAFE_DELETE(bullet);
			iter = bulletList.erase(iter);
		}
		else {
			iter++;
		}
	}
}
