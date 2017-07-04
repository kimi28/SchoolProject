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
	Rect* GetRect() { return rect; }

	void Initialize();
	void Destroy();
	void Update();
	void Render();

	void PlayerMemoryLink(Player* player) {
		playerMemoryLink = player;
	}

	void Collison();

	void ReMove(Bullet* bullet);

private:
	void Add(D3DXVECTOR2 coord);
	void Remove(Bullet* bullet);

	LPDIRECT3DDEVICE9 device;
	Sprite* sprite;
	vector<Bullet*> bulletList;


	LONG moveSpeed;
	D3DXVECTOR2 coord;
	float angle;

	DWORD time;

	Rect* rect;
	Player* playerMemoryLink;
};

