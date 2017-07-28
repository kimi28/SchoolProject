#pragma once

class Animation;

class Scene_02 : public Scene
{
public:
	Scene_02(LPDIRECT3DDEVICE9 device);
	~Scene_02();

	void Initialize() override;
	void Update() override;
	void Destroy() override;
	void Render() override;

private :
	Animation* animation;

	DWORD time;


	POINT frame;
};

