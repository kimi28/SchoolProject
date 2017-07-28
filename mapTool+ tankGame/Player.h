#pragma once

class Bullet;
class Sprite;
class Rect;
class Enemy;

class Player
{
public:
	Player(LPDIRECT3DDEVICE9 device);
	~Player();

	void Initialize();
	void Destroy();
	void Update();
	void Render();
	Rect* GetRect() { return rect; }

	void EnemyMemoryLink(Enemy* enemy) { enemymemoryLink = enemy; }

	void collison();

	void ReMove(Bullet* bullet);

private:
	LPDIRECT3DDEVICE9 device;

	Sprite* sprite;
	vector<Bullet*>bullets;

	static int bulletNum;

	Rect* rect;
	
	Enemy* enemymemoryLink;

};
