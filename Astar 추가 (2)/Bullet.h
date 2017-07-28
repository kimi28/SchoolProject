#pragma once

class Sprite;
class Rect;
class Bullet
{
public:
	Bullet(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 coord,
		float angle=0, float speed=10);
	~Bullet();

	bool GetIsOn() { return isOn; }
	void SetOn()
	{
		assert(isOn == false);
		isOn = true;
		 
		time = timeGetTime();
	}

	void SetCoord(D3DXVECTOR2 coord) { this->coord = coord; }
	void SetRotate(float angle);

	void Initialize();
	void Destroy();
	void Update();
	void Render(int bulletNum);

	Rect* GetRect() { return rect; }

private:
	LPDIRECT3DDEVICE9 device;

	Sprite* sprite;
	Sprite* sprite2;

	D3DXVECTOR2 coord;

	bool isOn;
	DWORD time;

	D3DXVECTOR2 velocity;
	float rotation;
	float speed;

	Rect* rect;
};

