#pragma once

class Bullet;
class Rect;
class Shooter
{
public:
	Shooter(LPDIRECT3DDEVICE9 device);
	~Shooter();

	virtual void Fire(D3DXVECTOR2 coord) = 0;

	virtual void Initialize();
	virtual void Destroy();
	virtual void Update();
	virtual void Render(int bulletNum);

protected:
	void Add(D3DXVECTOR2 coord);
	void Remove(Bullet* bullet);

	LPDIRECT3DDEVICE9 device;

	vector<Bullet*>bulletList;

	Rect* rect;
	D3DXVECTOR2 coord;
	float speed;
};

