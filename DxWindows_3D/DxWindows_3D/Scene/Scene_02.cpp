#include "../stdafx.h"
#include "Scene_02.h"
#include "../Render/TextureShader.h"
#include "../Render/Model.h"



Scene_02::Scene_02()
{
}


Scene_02::~Scene_02()
{
}

void Scene_02::Init()
{
	shader = new TextureShader;
	model = new Model(shader);
}

void Scene_02::Release()
{
	SAFE_DELETE(shader);
	SAFE_DELETE(model);
}

void Scene_02::Update(float timeDelta)
{
}

void Scene_02::Render()
{
	model->Render();
}
