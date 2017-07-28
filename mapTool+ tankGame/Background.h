#pragma once
#include "Sprite.h"

class Sprite;
class Background
{
public:
	Background(LPDIRECT3DDEVICE9 device);
	~Background();

	void Initialize();
	void Destroy();
	void Update();
	void Render();

private:
	LPDIRECT3DDEVICE9 device;
	Sprite* sprite;
};

