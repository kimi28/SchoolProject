#pragma once

class Bullet;
class BulletManager
{
public:
	static BulletManager* GetInstance();
	static void DeleteInstance();

	void SetDevice(LPDIRECT3DDEVICE9 device);
	void SetAngle(float angle) { this->angle = angle; }
	
	void Add(D3DXVECTOR2 coord);
	void Remove(Bullet* bullet);

	void Update();
	void Render();

private:
	BulletManager();
	~BulletManager();

	static BulletManager* instance;

	LPDIRECT3DDEVICE9 device;

	vector<Bullet*> bulletList;

	float angle;
};

