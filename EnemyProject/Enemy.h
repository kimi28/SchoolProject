#pragma once

class Sprite;
class Bullet;
class Rect;
class Player;
class Enemy
{
public:
	Enemy(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 coord);
	~Enemy();

	void SetCoord(D3DXVECTOR2 coord) { this->coord = coord; }
	D3DXVECTOR2 GetCoord() { return coord; }

	Rect* GetRect() { return rect; }

	void Initialize();
	void Destroy();
	void Update();
	void Render();

	void PlayerMemoryLink(Player* player) {
		playerMemoryLink = player;
	}

	void Collison();

	void Remove(Bullet* bullet);

private:
	LPDIRECT3DDEVICE9 device;
	Sprite* sprite;
	LONG moveSpeed;
	D3DXVECTOR2 coord;
	float angle;
	float bulletSpeed;

	DWORD time;

	Rect* rect;
	Player* playerMemoryLink;
};

