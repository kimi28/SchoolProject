#include "stdafx.h"
#include "Enemy.h"
#include "Sprite.h"
#include "Bullet.h"
#include "Rect.h"
#include "Player.h"
#include "Intersect.h"

int Enemy::bulletNum = 0;	

Enemy::Enemy(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 coord)
	: device(device)
	,coord(coord)
{
	Initialize();
}

Enemy::~Enemy()
{
	Destroy();
}

void Enemy::Initialize()
{
	sprite = new Sprite(device, L"Textures/SplitHorizon.tga");
	sprite->Initialize();

	sprite->SetCoord(coord);
	sprite->SetRotate(180);

	time = timeGetTime();

	rect = new Rect(device, coord, sprite->GetSize());


}

void Enemy::Destroy()
{
	sprite->Destory();
	SAFE_DELETE(sprite);
}

void Enemy::Update()
{
	
	D3DXVECTOR2 coord = sprite->GetCoord();
	float halfY = sprite->GetRealSize().y * 0.5f;

	DWORD currentTime = timeGetTime();

	int random = 1000 + rand() % 5 * 100;

	if (currentTime - time > random)
	{

		D3DXVECTOR2 point = coord;
		point.y += halfY;
		Bullet* bullet = new Bullet(device, point, 0, -10.0f);
		bullets.push_back(bullet);


		time = timeGetTime();
	}

	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i]->Update();
	}
	sprite->SetCoord(coord);
	rect->SetCoord(coord);

	//collison();
}

void Enemy::Render()
{
	sprite->Render();

	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i]->Render(bulletNum);
	}
}

void Enemy::collison()
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		if (Intersect::IsContainRect(NULL, bullets[i]->GetRect(), playerMemory->GetRect()))
		{
			
		}
	}
}
