#include "stdafx.h"
#include "EnemyManager.h"
#include "Enemy.h"

EnemyManager * EnemyManager::instance = NULL;

EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
	for (size_t i = 0; i < enemyList.size(); i++)
	{
		SAFE_DELETE(enemyList[i]);
	}
}

EnemyManager * EnemyManager::GetInstance()
{
	if (instance == NULL)
		instance = new EnemyManager;

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

void EnemyManager::Add()
{
	count++;
}

void EnemyManager::SettingEnemy(int enemyCount)
{

	POINT position = { enemyCount / 5 + 1,5 };

	for (int i = 0; i < position.x; i++)
	{

		if (i == position.x - 1)
		{
			position.y = enemyCount % 5;
		}
		for (int j = 0; j < position.y; j++)
		{
			Enemy* enemy = new Enemy(device, {(FLOAT) 900 - i * 100, (FLOAT)j * 150 + 50 });
			//enemy->Initialize();

			enemyList.push_back(enemy);
		}
	}

}

void EnemyManager::Remove(Enemy* enemy)
{
	vector<Enemy*> ::iterator iter = enemyList.begin();
	for (iter; iter != enemyList.end();)
	{
		if ((*iter) == enemy)
		{
			SAFE_DELETE(enemy);
			iter = enemyList.erase(iter);
		}
		else
			iter++;
	}
}

void EnemyManager::Update()
{
	for (size_t i = 0; i < enemyList.size(); i++)
	{
		enemyList[i]->Update();
	}
}

void EnemyManager::Render()
{
	for (size_t i = 0; i < enemyList.size(); i++)
	{
		enemyList[i]->Render();
	}

}