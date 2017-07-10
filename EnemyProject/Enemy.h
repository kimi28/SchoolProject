#pragma once

class Sprite;
class Bullet;
class Rect;
class Player;
class Enemy
{
public:
	Enemy(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 coord, float angle =0, float moveSpeed = 2, float removeSec =2);
	~Enemy();

	void SetCoord(D3DXVECTOR2 coord) { this->coord = coord; }
	D3DXVECTOR2 GetCoord() { return coord; }

	Rect* GetRect() { return rect; }

	bool GetIsOn() { return isOn; }
	void SetOn() {
		assert(isOn == false);

		isOn = true;
	}

	void SetOff() {
		assert(isOn == true);

		isOn = false;

		time = timeGetTime();
	}

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
	D3DXVECTOR2 coord;
	float moveSpeed;
	float angle;
	float bulletSpeed;

	DWORD time;

	Rect* rect;
	Player* playerMemoryLink;

	bool isOn;
	float removeSec;
};

