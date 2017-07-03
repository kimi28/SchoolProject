#pragma once

class Sprite;
class Bullet;
class Player
{
public:
	Player(LPDIRECT3DDEVICE9 device);
	~Player();

	void SetCoord(D3DXVECTOR2 coord) { this->coord = coord; }

	void Initialize();
	void Destroy();
	void Update();
	void Render();

private:
	void Add(D3DXVECTOR2 coord);
	void Remove(Bullet* bullet);

	LPDIRECT3DDEVICE9 device;
	Sprite* sprite;
	LONG moveSpeed;
	D3DXVECTOR2 coord;
	vector<Bullet*> bulletList;

	float angle;
};