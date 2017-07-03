#pragma once

class Enemy;

class EnemyManager
{
public:
	static EnemyManager* GetInstance();
	static void DeleteInstance();

	void SetDevice(LPDIRECT3DDEVICE9 device);

	void Add();

	void SettingEnemy(int enemyCount);

	void Remove(Enemy* enemy);

	void Update();
	void Render();
private:
	EnemyManager();
	~EnemyManager();

	static EnemyManager* instance;
	LPDIRECT3DDEVICE9 device;

	vector<Enemy*> enemyList;

	int count;
};