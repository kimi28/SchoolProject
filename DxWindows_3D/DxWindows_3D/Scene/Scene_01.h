#pragma once
#include "Scene.h"

class Cube;
class ColorShader;
class Scene_01 : public Scene
{
	Cube* model[6];
	ColorShader* colorShader;

public:
	Scene_01();
	~Scene_01();

	void Init() override;
	void Release() override;
	void Update(float timeDelta) override;
	void Render() override;
};

