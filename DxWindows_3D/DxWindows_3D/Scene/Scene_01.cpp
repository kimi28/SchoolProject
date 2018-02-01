#include "../stdafx.h"
#include "Scene_01.h"

#include "../Render/Model.h"
#include "../Render/Cube.h"
#include "../Render/Star.h"
#include "../Render/ColorShader.h"



Scene_01::Scene_01()
{
}


Scene_01::~Scene_01()
{
}

void Scene_01::Init()
{
	colorShader = new ColorShader();
	for (int i = 0; i < 6; i++)
	{
		model[i] = new Cube(colorShader);
	}

	//¸Ó¸®
	model[0]->GetTransform()->SetWorldPosition(0, 1.5f, 0);
	model[0]->GetTransform()->SetScale(0.5f, 0.5f, 0.5f);
	//¸öÅë
	model[1]->GetTransform()->SetWorldPosition(0, 0, 0);
	model[1]->GetTransform()->SetScale(1.0f, 1.0f, 0.5f);

	//ÆÈ
	model[2]->GetTransform()->SetWorldPosition(-1.5f, 0, 0);
	model[2]->GetTransform()->SetScale(0.5f, 1.0f, 0.5f);

	model[3]->GetTransform()->SetWorldPosition(1.5f, 0, 0);
	model[3]->GetTransform()->SetScale(0.5f, 1.0f, 0.5f);
	//´Ù¸®
	model[4]->GetTransform()->SetWorldPosition(0.5f, -2.0f, 0);
	model[4]->GetTransform()->SetScale(0.5f, 1.0f, 0.5f);

	model[5]->GetTransform()->SetWorldPosition(-0.5f, -2.0f, 0);
	model[5]->GetTransform()->SetScale(0.5f, 1.0f, 0.5f);

}

void Scene_01::Release()
{
	SAFE_DELETE(colorShader);
}

void Scene_01::Update(float timeDelta)
{
}

void Scene_01::Render()
{
	for (int i = 0; i < 6; i++)
		model[i]->Render();
}
