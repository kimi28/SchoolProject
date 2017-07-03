#include "stdafx.h"
#include "Player.h"
#include "Sprite.h"
#include "Bullet.h"

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
}

void Player::Destroy()
{
	for (size_t i = 0; i < bulletList.size(); i++) {
		SAFE_DELETE(bulletList[i]);
	}
	sprite->Destroy();
	SAFE_DELETE(sprite);

}

void Player::Update()
{
	if (Keyboard::GetInstance()->KeyPress(VK_UP)) {
		coord.y -= moveSpeed;
	}
	else if(Keyboard::GetInstance()->KeyPress(VK_DOWN)){
		coord.y += moveSpeed;
	}
	sprite->SetCoord(coord);

	if (Keyboard::GetInstance()->KeyDown(VK_SPACE)) {
		D3DXVECTOR2 point1 = coord;
		point1.x += 40;
		point1.y += 40;

		Add(point1);


		D3DXVECTOR2 point2 = coord;
		point2.x += 40;
		point2.y += 15;

		Add(point2);
	}

	for (size_t i = 0; i < bulletList.size(); i++) {
		bulletList[i]->Update();
	}

}

void Player::Render()
{
	for (size_t i = 0; i < bulletList.size(); i++) {
		bulletList[i]->Render();
	}
	sprite->Render();
}

void Player::Add(D3DXVECTOR2 coord)
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
		Bullet* bullet = new Bullet(device, coord, angle);
		bullet->SetOn();
		bulletList.push_back(bullet);
	}
}

void Player::Remove(Bullet * bullet)
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

