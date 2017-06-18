#pragma once

class Rect;
class Bullet;

class Monster
{
public:
	Monster(LPDIRECT3DDEVICE9 device);
	~Monster();

	void SetCoord(POINT coord) { this->coord = coord; }

	void Initialize();
	void Destroy();
	void Update();
	void Render();

private:
	LPDIRECT3DDEVICE9 device;

	LONG moveSpeed;
	POINT coord;
	Rect* rect;

};