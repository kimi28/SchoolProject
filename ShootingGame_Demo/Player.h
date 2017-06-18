#pragma once

class Rect;
class Bullet;
class Player
{
public:
	Player(LPDIRECT3DDEVICE9 deivce, POINT coord);
	~Player();

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

	vector<Bullet*> bulletList;
};

