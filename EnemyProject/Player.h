#pragma once

class Sprite;
class Bullet;
class Rect;
class Enemy;
class Player
{
public:
	Player(LPDIRECT3DDEVICE9 device);
	~Player();

	void SetCoord(D3DXVECTOR2 coord) { this->coord = coord; }

	Rect* GetRect() { return rect; }

	void Initialize();
	void Destroy();
	void Update();
	void Render();

	void EnemyMemoryLink(Enemy* enemy) {
		enemyMemoryLink = enemy;
	}

	void Collison();

	void ReMove(Bullet* bullet);
	void ReMove(Enemy* enemy);

private:
	void Add(D3DXVECTOR2 coord);
	void Remove(Bullet* bullet);

	LPDIRECT3DDEVICE9 device;
	Sprite* sprite;
	LONG moveSpeed;
	D3DXVECTOR2 coord;
	vector<Bullet*> bulletList;

	float angle;

	Rect* rect;

	Enemy* enemyMemoryLink;
};