#pragma once
#include "Scene.h"

class Cube;
class ColorShader;
class Scene_01 : public Scene
{
	Cube* model[6];
	ColorShader* colorShader;

	float maxAngle;
	float minAngle;
	float currentAngle;
	float countAngle;
	bool turn;

	float angleY = 0.0f;

public:
	Scene_01();
	~Scene_01();

	void Init() override;
	void Release() override;
	void Update(float timeDelta) override;
	void Render() override;
};

