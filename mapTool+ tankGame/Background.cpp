#include "stdafx.h"
#include "Background.h"
#include "Sprite.h"

Background::Background(LPDIRECT3DDEVICE9 device)
	: device(device)
{
	Initialize();
}

Background::~Background()
{
	Destroy();
}

void Background::Initialize()
{
	sprite = new Sprite[3];

	for (int i = 0; i < 3; i++)
	{
		sprite[i] = Sprite(device, L"Textures/Craters.tga", D3DXVECTOR2(-100 + (i * 1024), 0));
		sprite[i].Initialize();
	}
}

void Background::Destroy()
{
	for (int i = 0; i < 3; i++)
		sprite[i].Destory();

	SAFE_DELETE_ARRAY(sprite);
}

void Background::Update()
{
	for (int i = 0; i < 3; i++)
	{
		if (sprite[i].GetCoord().x + sprite[i].GetSize().x <= 0)
		{
			int max = -9999;
			for (int j = 0; j < 3; j++)
			{
				int temp = sprite[j].GetCoord().x + sprite[j].GetSize().x;

				if (temp > max)
					max = temp;
			}


			sprite[i].SetCoord(D3DXVECTOR2(max, 0));
		}

		D3DXVECTOR2 coord = sprite[i].GetCoord();
		coord.x -= 5.0f;
		sprite[i].SetCoord(coord);
	}
}

void Background::Render()
{
	for (int i = 0; i < 3; i++)
		sprite[i].Render();
}
