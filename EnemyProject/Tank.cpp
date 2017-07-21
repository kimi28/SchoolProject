#include "stdafx.h"
#include "Tank.h"
#include "Animation.h"
#include "TileMap.h"
#include "Rect.h"


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
	x = 0;
	y = 0;
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
	rect = { (LONG)x, (LONG)y, (LONG)x + TILESIZE, (LONG)y + TILESIZE };

	animation->Update(frame);
}

void Tank::Render()
{
	animation->Render();
}

void Tank::TankMove()
{
	RECT rectCollision;
	int tileX, tileY;
	
	rectCollision = rect;

	switch (direction)
	{
	case TANKDIRECTION_LEFT:
		frame = { 0,3 };
		x -= 1.0f;
		animation->SetCoord({ x, y });
		rectCollision = { (LONG)x, (LONG)y, (LONG)x + TILESIZE, (LONG)y + TILESIZE };
		break;
	case TANKDIRECTION_RIGHT:
		frame = { 0,2 };
		x += 1.0f;
		animation->SetCoord({ x, y });
		rectCollision = { (LONG)x, (LONG)y, (LONG)x + TILESIZE, (LONG)y + TILESIZE };
		break;
	case TANKDIRECTION_UP:
		frame = { 0,0 };
		y -= 1.0f;
		animation->SetCoord({ x, y });
		rectCollision = { (LONG)x, (LONG)y, (LONG)x + TILESIZE, (LONG)y + TILESIZE };
		break;
	case TANKDIRECTION_DOWN:
		frame = { 0,1 };
		y += 1.0f;
		animation->SetCoord({ x, y });
		rectCollision = { (LONG)x, (LONG)y, (LONG)x + TILESIZE, (LONG)y + TILESIZE };
		break;
	}

	rectCollision.left += 1;
	rectCollision.right -= 1;
	rectCollision.top += 1;
	rectCollision.bottom -= 1;

	tileX = rectCollision.left / TILESIZE;
	tileY = rectCollision.top / TILESIZE;

	int tileIndex[2];

	switch (direction)
	{
	case TANKDIRECTION_LEFT:
		tileIndex[0] = tileX + tileY* TILEX;
		tileIndex[1] = tileIndex[0] - 1;
		break;
	case TANKDIRECTION_RIGHT:
		tileIndex[0] = tileX + tileY* TILEX;
		tileIndex[1] = tileIndex[0] + 1;
		break;
	case TANKDIRECTION_UP:
		tileIndex[0] = tileX + tileY* TILEY;
		tileIndex[1] = tileIndex[0] - TILEX;
		break;
	case TANKDIRECTION_DOWN:
		tileIndex[0] = tileX + tileY* TILEY;
		tileIndex[1] = tileIndex[0] + TILEX;
		break;
	}

	if (tileIndex[1] < 0 || tileIndex[1]>400) {
		tileIndex[1] = tileIndex[0];
	}
	for (int i = 0; i < 2; i++) {
		RECT rect1;
		if (((tileMap->GetAttribute()[tileIndex[i] & ATTR_UMMOVE]) == ATTR_UMMOVE) &&
			IntersectRect(&rect1, &tileMap->GetTiles()[tileIndex[i]].rect->GetRect(), &rectCollision)) {
			switch (direction)
			{
			case TANKDIRECTION_LEFT:
				rect.left = tileMap->GetTiles()[tileIndex[i]].rect->GetRect().right;
				rect.right = rect.left + 30;
				x = rect.left;
				break;
			case TANKDIRECTION_RIGHT:
				rect.right = tileMap->GetTiles()[tileIndex[i]].rect->GetRect().left;
				rect.left = rect.right - 30;
				x = rect.right;
				break;
			case TANKDIRECTION_UP:
				rect.top = tileMap->GetTiles()[tileIndex[i]].rect->GetRect().bottom;
				rect.bottom = rect.top + 30;
				y = rect.top;
				break;
			case TANKDIRECTION_DOWN:
				rect.bottom = tileMap->GetTiles()[tileIndex[i]].rect->GetRect().top;
				rect.top = rect.bottom - 30;
				y = rect.bottom;
				break;
			}
		}
	}
}

void Tank::SetTankPosition()
{
}
