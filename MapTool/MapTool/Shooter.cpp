#include "stdafx.h"
#include "Shooter.h"
#include "Bullet.h"

Shooter::Shooter(LPDIRECT3DDEVICE9 device)
	:device(device)
{
}

Shooter::~Shooter()
{
}

void Shooter::Add(POINT coord)
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
	}
	else {
		Bullet* bullet = new Bullet(device, coord, 20);
		bullet->SetOn();
		bulletList.push_back(bullet);
	}
}

void Shooter::Remove(Bullet* bullet)
{
	for (vector<Bullet*>::iterator iter = bulletList.begin();
		iter != bulletList.end();)
	{
		if ((*iter) == bullet) {
			SAFE_DELETE(bullet);
			iter = bulletList.erase(iter);
		}
		else
			iter++;
	}
}