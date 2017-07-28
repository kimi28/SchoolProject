#pragma once


//≈ ≈© 4πÊ«‚
class Animation;
class TankMap;
enum TANKDIRECTION
{
	TANKDIRECTION_LEFT,
	TANKDIRECTION_RIGHT,
	TANKDIRECTION_UP,
	TANKDIRECTION_DOWN
};

class tank 
{
private:
	TANKDIRECTION _direction;
	LPDIRECT3DDEVICE9 device;

	Animation* _animation;
	RECT _rc;
	float _x, _y;
	float _speed;

	int tileIndex[2];	//≈∏¿œ ¿Œµ¶Ω∫

	POINT frame;
	TankMap* _tankMap;

public:
	tank(LPDIRECT3DDEVICE9 device);
	~tank();

	HRESULT init();
	void release();
	void update();
	void render();

	void tankMove();
	RECT RectMakeCenter(int x, int y, int width, int height);
	void setTankPosition();

	void setTankMapMemoryLink(TankMap* tm) { _tankMap = tm; }

};

