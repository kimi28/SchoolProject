#pragma once
#include "Scene.h"

class TextureShader;
class Model;
class Scene_02 : public Scene
{

	Model* model;
	TextureShader* shader;
public:
	Scene_02();
	~Scene_02();

	void Init()	override;
	void Release()	override;
	void Update(float timeDelta)	override;
	void Render()	override;

};

