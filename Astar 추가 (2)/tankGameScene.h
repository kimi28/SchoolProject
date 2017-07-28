#pragma once

class tank;
class TankMap;
class tankGameScene : public Scene
{
private:
	TankMap* _tankMap;
	tank* _tank;

	LPDIRECT3DDEVICE9 device;
public:
	tankGameScene(LPDIRECT3DDEVICE9 device);
	~tankGameScene();
	void Initialize() ;
	void Update() ;
	void Destroy() ;
	void Render() ;
};

