#pragma once

class Bullet;
class Sprite;
class Rect;
class Player;
class Enemy
{
public:
	Enemy(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 coord);
	~Enemy();
	
	Rect* GetRect() { return rect; }
	vector<Bullet*> GetBullet() { return bullets; }

	
	void Initialize();
	void Destroy();
	void Update();
	void Render();
	
	void collison();
	void PlayerMemoryLink(Player* player) { playerMemory = player; }

private:
	LPDIRECT3DDEVICE9 device;

	Sprite* sprite;
	vector<Bullet*>bullets;

	D3DXVECTOR2 coord;

	Rect* rect;

	DWORD time;

	static int bulletNum;

	Player* playerMemory;


};

