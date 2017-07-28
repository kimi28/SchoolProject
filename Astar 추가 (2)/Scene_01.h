#pragma once
#include "Scene.h"

class Player;
class Scene_01 : public Scene
{
public:
	Scene_01(LPDIRECT3DDEVICE9 device);
	~Scene_01();

	void Initialize( ) override;
	void Update() override;
	void Destroy() override;
	void Render() override;
private:
	
	Player* player;
};

