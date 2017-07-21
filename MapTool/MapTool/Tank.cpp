#include "stdafx.h"
#include "Tank.h"
#include "Animation.h"
#include "TileMap.h"


Tank::Tank(LPDIRECT3DDEVICE9 device)
	: device(device)
{
	Initialize();
}


Tank::~Tank()
{
}

void Tank::Initialize()
{
	direction = TANKDIRECTION_RIGHT;
	x = 100;
	y = 100;
	animation = new Animation(device, L"Textures/tank.bmp", { 8,4 }, { x, y });
	frame = { 0,0 };
}

void Tank::Destroy()
{
	SAFE_DELETE(animation);
}

void Tank::Update()
{
	if (Keyboard::GetInstance()->KeyPress(VK_LEFT)) {
		direction = TANKDIRECTION_LEFT;
		TankMove();
	}
	if (Keyboard::GetInstance()->KeyPress(VK_RIGHT)) {
		direction = TANKDIRECTION_RIGHT;
		TankMove();
	}
	if (Keyboard::GetInstance()->KeyPress(VK_UP)) {
		direction = TANKDIRECTION_UP;
		TankMove();
	}
	if (Keyboard::GetInstance()->KeyPress(VK_DOWN)) {
		direction = TANKDIRECTION_DOWN;
		TankMove();
	}
	animation->SetCoord({ x, y });
	animation->Update(frame);
}

void Tank::Render()
{
	animation->Render();
}

void Tank::TankMove()
{
	switch (direction)
	{
	case TANKDIRECTION_LEFT:
		frame = { 0,3 };
		x -= 1.0f;
		break;
	case TANKDIRECTION_RIGHT:
		frame = { 0,2 };
		x += 1.0f;
		break;
	case TANKDIRECTION_UP:
		frame = { 0,0 };
		y -= 1.0f;
		break;
	case TANKDIRECTION_DOWN:
		frame = { 0,1 };
		y += 1.0f;
		break;
	}
}

void Tank::SetTankPosition()
{
}
