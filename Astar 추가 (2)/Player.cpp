#include "stdafx.h"
#include "Player.h"
#include "Sprite.h"
#include "Bullet.h"
#include "Rect.h"
#include "Enemy.h"
#include "Intersect.h"

int Player::bulletNum = 0;

Player::Player(LPDIRECT3DDEVICE9 device)
	: device(device)
{
	Initialize();
}

Player::~Player()
{
	Destroy();
}

void Player::Initialize()
{
	sprite = new Sprite(device, L"Textures/SplitHorizon.tga");
	sprite->Initialize();

	D3DVIEWPORT9 viewport;
	device->GetViewport(&viewport);

	float halfY = viewport.Height * 0.5f;
	float spriteHalfY = sprite->GetRealSize().y * 0.5f;

	sprite->SetCoord(D3DXVECTOR2(30 + viewport.Width, halfY - spriteHalfY));

	rect = new Rect(device, D3DXVECTOR2(30, halfY - spriteHalfY), sprite->GetSize());
	rect->Initialize();
}

void Player::Destroy()
{
	sprite->Destory();
	SAFE_DELETE(sprite);
	//rect->Destroy();
	//SAFE_DELETE(rect);
}

void Player::Update()
{
	

	D3DXVECTOR2 coord = sprite->GetCoord();
	float halfY = sprite->GetRealSize().y * 0.5f;

	if (Keyboard::GetInstance()->KeyPress(VK_UP))
		coord.y -= 5;
	else if (Keyboard::GetInstance()->KeyPress(VK_DOWN))
		coord.y += 5;
	else if (Keyboard::GetInstance()->KeyPress(VK_LEFT))
		coord.x -= 5;
	else if (Keyboard::GetInstance()->KeyPress(VK_RIGHT))
		coord.x += 5;

	if (Keyboard::GetInstance()->KeyDown(VK_SPACE))
	{
		D3DXVECTOR2 point = coord;
		point.x += sprite->GetSize().x - 10;
		point.y += halfY;

		Bullet* bullet = new Bullet(device, point);
		bullets.push_back(bullet);
	}
	

	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i]->Update();
	}
	sprite->SetCoord(coord);
	rect->SetCoord(coord);

//	collison();
}

void Player::Render()
{
	sprite->Render();
	for (size_t i = 0; i < bullets.size(); i++)
	{
			bullets[i]->Render(bulletNum);
	}
}

void Player::collison()
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		if (Intersect::IsContainRect(NULL, bullets[i]->GetRect(),enemymemoryLink->GetRect()))
		{
			ReMove(bullets[i]);
		}
	}

}

void Player::ReMove(Bullet * bullet)
{
	auto iter = bullets.begin();
	for(iter; iter != bullets.end();)
	{
		if ((*iter) == bullet)
		{
			SAFE_DELETE(bullet);
			iter = bullets.erase(iter);
		}
		else
		{
			iter++;
		}
	}

}


