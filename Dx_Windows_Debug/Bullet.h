#pragma once

class Circle;
class Bullet
{
public:
	Bullet(LPDIRECT3DDEVICE9 device, POINT coord);
	~Bullet();

	void Initialize();
	void Destroy();
	void Update();
	void Render();

private:
	LPDIRECT3DDEVICE9 device;

	Circle* circle;
	POINT coord;
};

