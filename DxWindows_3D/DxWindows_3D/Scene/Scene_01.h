#pragma once
#include "Scene.h"

class Scene_01 : public Scene
{
public:
	Scene_01();
	~Scene_01();

	void Init() override;
	void Release() override;
	void Update(float timeDelta) override;
	void Render() override;
};

