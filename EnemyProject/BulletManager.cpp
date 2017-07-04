#include "stdafx.h"
#include "BulletManager.h"
#include "Bullet.h"

BulletManager* BulletManager::instance = NULL;

BulletManager::BulletManager()
{

}


BulletManager::~BulletManager()
{
	for (size_t i = 0; i < bulletList.size(); i++) {
		SAFE_DELETE(bulletList[i]);
	}
}

BulletManager * BulletManager::GetInstance()
{
	if (instance == NULL)
		instance = new BulletManager();

	return instance;
}

void BulletManager::DeleteInstance()
{
	SAFE_DELETE(instance);
}

void BulletManager::SetDevice(LPDIRECT3DDEVICE9 device)
{
	this->device = device;
}

void BulletManager::Add(D3DXVECTOR2 coord)
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

void BulletManager::Remove(Bullet * bullet)
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

void BulletManager::Update()
{
	for (size_t i = 0; i < bulletList.size(); i++) {
		bulletList[i]->Update();
	}
}

void BulletManager::Render()
{
	for (size_t i = 0; i < bulletList.size(); i++) {
		bulletList[i]->Render();
	}
}
