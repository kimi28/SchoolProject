#pragma once

class Sprite;
class Bullet;
class Enemy
{
public:
	Enemy(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 coord);
	~Enemy();

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

	DWORD time;

	float angle;
};

