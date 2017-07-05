#pragma once

class Bullet;
class Player;
class Enemy;
class BulletManager
{
public:
	static BulletManager* GetInstance();
	static void DeleteInstance();

	void SetDevice(LPDIRECT3DDEVICE9 device);
	void SetAngle(float angle) { this->angle = angle; }
	void SetSpeed(float speed) { this->speed = speed; }
	
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
	float speed;
};

