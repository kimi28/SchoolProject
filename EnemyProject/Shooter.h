#pragma once

class Bullet;
class Rect;
class Shooter
{
public:
	Shooter(LPDIRECT3DDEVICE9 device);
	~Shooter();

	virtual void Fire(POINT coord) = 0;

	virtual void Initialize();
	virtual void Destroy();
	virtual void Update();
	virtual void Render();

protected:
	void Add(POINT coord);
	void Remove(Bullet* bullet);

	LPDIRECT3DDEVICE9 device;

	vector <Bullet * > bulletList;

	Rect* rect;
	POINT coord;
	float speed;

};