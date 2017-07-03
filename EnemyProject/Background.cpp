#include "stdafx.h"
#include "Background.h"
#include "Sprite.h"

Background::Background(LPDIRECT3DDEVICE9 device)
	: device(device)
{

}

Background::~Background()
{

}

void Background::Initialize()
{
	sprite = new Sprite[3];
	sprite[0] = Sprite(device, L"Textures/Craters.tga", D3DXVECTOR2(-100, 0));
	sprite[1] = Sprite(device, L"Textures/Craters.tga", D3DXVECTOR2(668, 0));
	sprite[2] = Sprite(device, L"Textures/Craters.tga", D3DXVECTOR2(1436, 0));
	for (int i = 0; i < 3; i++) {
		sprite[i].Initialize();
	}
	//sprite = new Sprite(device, L"Textures/Craters.tga", D3DXVECTOR2(0, 0));
	//sprite->Initialize();
}

void Background::Destroy()
{
	for (int i = 0; i < 3; i++) {
		sprite[i].Destroy();
	}
	SAFE_DELETE_ARRAY(sprite);
}

void Background::Update()
{
	for (int i = 0; i < 3; i++) {
		if (sprite[i].GetCoord().x + sprite[i].GetSize().x <= 0)
		{
			int number = 0;
			if (i == 0) {
				number = 2;
			}
			else {
				number = i-1;
			}
			D3DXVECTOR2 coord = sprite[number].GetCoord();
			coord.x += sprite[number].GetSize().x;
			sprite[i].SetCoord(coord);
		}

		D3DXVECTOR2 coord = sprite[i].GetCoord();
		coord.x -= 5.0f;
		sprite[i].SetCoord(coord);
	}
}

void Background::Render()
{
	for (int i = 0; i < 3; i++) {
	sprite[i].Render();
	}

}
