#include "stdafx.h"
#include "Player.h"
#include "Rect.h"
#include "Bullet.h"



Player::Player(LPDIRECT3DDEVICE9 device, POINT coord)
	: device(device)
	, coord(coord)
	, moveSpeed(5)
{
	Initialize();
}


Player::~Player()
{
	Destroy();
}

void Player::Initialize()
{
	rect = new Rect(device, coord, { 40, 40 }, 0xFF0000FF);
	rect->Initialize();


}

void Player::Destroy()
{
	for (size_t i = 0; i < bulletList.size(); i++) {
		SAFE_DELETE(bulletList[i]);
	}
	rect->Destroy();
	SAFE_DELETE(rect);
}

void Player::Update()
{
	if (Keyboard::GetInstance()->KeyPress(VK_UP)) {
		coord.y -= moveSpeed;
	}
	else if (Keyboard::GetInstance()->KeyPress(VK_DOWN)) {
		coord.y += moveSpeed;
	}
	//if (Keyboard::GetInstance()->KeyPress(VK_LEFT)) {
	//	coord.x -= moveSpeed;
	//}
	//else if (Keyboard::GetInstance()->KeyPress(VK_RIGHT)) {
	//	coord.x += moveSpeed;
	//}
	rect->SetCoord(coord);

	if (Keyboard::GetInstance()->KeyDown(VK_SPACE)) {
		POINT point = coord;
		point.x += 40;
		point.y += 20;
		Bullet* bullet = new Bullet(device, point);
		bulletList.push_back(bullet);
	}

	for (size_t i = 0; i < bulletList.size(); i++) {
		bulletList[i]->Update();
	}

}


void Player::Render()
{
	rect->Render();

	for (size_t i = 0; i < bulletList.size(); i++) {
		bulletList[i]->Render();
	}
}
