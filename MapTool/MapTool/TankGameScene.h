#pragma once

class TileMap;
class Tank;
class TankGameScene : public Scene
{
public:
	TankGameScene(LPDIRECT3DDEVICE9 device);
	~TankGameScene();

	void Initialize();
	void Destroy();
	void Update();
	void Render();

private:
	LPDIRECT3DDEVICE9 device;
	Tank* tank;
	TileMap* tileMap;
};

