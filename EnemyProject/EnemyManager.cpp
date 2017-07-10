#include "stdafx.h"
#include "EnemyManager.h"
#include "Enemy.h"

EnemyManager* EnemyManager::instance = NULL;

EnemyManager * EnemyManager::GetInstance()
{
	if (instance == NULL)
		instance = new EnemyManager();
	return instance;
}

void EnemyManager::DeleteInstance()
{
	SAFE_DELETE(instance);
}

void EnemyManager::SetDevice(LPDIRECT3DDEVICE9 device)
{
	this->device = device;
}

void EnemyManager::Add(D3DXVECTOR2 coord)
{
	int number = -1;
	for (size_t i = 0; i < enemyList.size(); i++) {
		if (enemyList[i]->GetIsOn() == false) {
			number = (int)i;
			break;
		}
	}

	if (number > -1) {
		enemyList[number]->SetOn();
		enemyList[number]->SetCoord(coord);
	}
	else {
		Enemy* enemy = new Enemy(device, coord);
		enemy->SetOn();
		enemyList.push_back(enemy);
	}
}

void EnemyManager::Remove(Enemy * enemy)
{
	for (vector<Enemy*>::iterator iter = enemyList.begin();
		iter != enemyList.end();) {
		if ((*iter) == enemy) {
			SAFE_DELETE(enemy);
			iter = enemyList.erase(iter);
		}
		else {
			iter++;
		}
	}
}

void EnemyManager::Update()
{
	for (size_t i = 0; i < enemyList.size(); i++) {
		enemyList[i]->Update();
	}
}

void EnemyManager::Render()
{
	for (size_t i = 0; i < enemyList.size(); i++) {
		enemyList[i]->Render();
	}
}

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
	for (size_t i = 0; i < enemyList.size(); i++) {
		SAFE_DELETE(enemyList[i]);
	}
}
