#pragma once
class Animation;
class TileMap;

enum TANKDIRECTION {
	TANKDIRECTION_LEFT,
	TANKDIRECTION_RIGHT,
	TANKDIRECTION_UP,
	TANKDIRECTION_DOWN
};

class Tank
{
public:
	Tank(LPDIRECT3DDEVICE9 device);
	~Tank();

	void Initialize();
	void Destroy();
	void Update();
	void Render();

	void TankMove();
	void SetTankPosition();

	void SetTankMapMemoryLink(TileMap * tm) { tileMap = tm; }
private:
	LPDIRECT3DDEVICE9 device;
	Animation * animation;
	float x;
	float y;
	POINT frame;
	TileMap* tileMap;

	RECT rect;
	TANKDIRECTION direction;
};

