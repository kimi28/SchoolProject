#include "../stdafx.h"
#include "Scene_01.h"

#include "../Render/Model.h"
#include "../Render/Cube.h"
#include "../Render/Star.h"
#include "../Render/ColorShader.h"
#include "../Render/TextureShader.h"

Scene_01::Scene_01()
{
}


Scene_01::~Scene_01()
{
}

void Scene_01::Init()
{

	colorShader = new TextureShader();
	for (int i = 0; i < 6; i++)
	{
		model[i] = new Cube(colorShader);
	}
	ST_TEXTURE_RANGE stRange;

	// 赣府
	stRange.vMin = D3DXVECTOR2(0.0f, 0.0f);
	stRange.vMax = D3DXVECTOR2(0.5f, 0.5f);
	model[0]->CreateVertexBuffer(stRange, 2, 2, 2);

	// 个烹
	stRange.vMin = D3DXVECTOR2(4.0f / 16.0f, 0.5f);
	stRange.vMax = D3DXVECTOR2(10.0f / 16.0f, 1.0f);

	model[1]->CreateVertexBuffer(stRange, 2, 3, 1);

	stRange.vMin = D3DXVECTOR2(10.0f / 16.0f, 0.5f);
	stRange.vMax = D3DXVECTOR2(14.0f / 16.0f, 1.0f);
	model[2]->CreateVertexBuffer(stRange, 1, 3, 1);
	model[3]->CreateVertexBuffer(stRange, 1, 3, 1);

	// 坷弗促府
	stRange.vMin = D3DXVECTOR2(0.0f, 0.5f);
	stRange.vMax = D3DXVECTOR2(0.25f, 1.0f);
	model[4]->CreateVertexBuffer(stRange, 1, 3, 1);
	model[5]->CreateVertexBuffer(stRange, 1, 3, 1);

	for (int i = 0; i < 6; i++)
	{
		model[i]->CreateIndexBuffer();
	}

	//赣府
	model[0]->GetTransform()->SetWorldPosition(0, 1.5f, 0);
	model[0]->GetTransform()->SetScale(0.5f, 0.5f, 0.5f);
	//个烹
	model[1]->GetTransform()->SetWorldPosition(0, 0, 0);
	model[1]->GetTransform()->SetScale(1.0f, 1.0f, 0.5f);

	//迫
	model[2]->GetTransform()->SetWorldPosition(-1.5f, 0, 0);
	model[2]->GetTransform()->SetScale(0.5f, 1.0f, 0.5f);

	model[3]->GetTransform()->SetWorldPosition(1.5f, 0, 0);
	model[3]->GetTransform()->SetScale(0.5f, 1.0f, 0.5f);
	//促府
	model[4]->GetTransform()->SetWorldPosition(0.5f, -2.0f, 0);
	model[4]->GetTransform()->SetScale(0.5f, 1.0f, 0.5f);

	model[5]->GetTransform()->SetWorldPosition(-0.5f, -2.0f, 0);
	model[5]->GetTransform()->SetScale(0.5f, 1.0f, 0.5f);

	currentAngle = 0.0f;
	countAngle = 0.0f;
	maxAngle = 35.0f*ONE_RAD;
	minAngle = -35.0f*ONE_RAD;
	turn = false;

}

void Scene_01::Release()
{
	SAFE_DELETE(colorShader);
}

void Scene_01::Update(float timeDelta)
{
	float deltaMove = 3.0f *timeDelta;
	float deltaAngle = 90.0f * ONE_RAD * timeDelta;

	if (INPUT->GetKey(VK_RBUTTON) == false)
	{
		D3DXVECTOR3 axis[3];
		model[1]->GetTransform()->GetUnitAxies(axis);
		D3DXVECTOR3 position
			= model[1]->GetTransform()->GetWorldPosition();
		if (INPUT->GetKey('D'))
		{
			angleY += deltaAngle;
			for (int i = 0; i < 6; i++)
				model[i]->GetTransform()->RotateWorld(0, angleY, 0);
		}
		model[0]->GetTransform()
			->SetWorldPosition(position + axis[1] / 2);
		model[2]->GetTransform()
			->SetWorldPosition(position - axis[0]);
		model[3]->GetTransform()
			->SetWorldPosition(position + axis[0]);
		model[4]->GetTransform()
			->SetWorldPosition(position - axis[0]/2
			-axis[1]);
		model[5]->GetTransform()
			->SetWorldPosition(position + axis[0]/2
			-axis[1]);


		if (INPUT->GetKey('W'))
		{
			model[1]->GetTransform()->
				MovePositionLocal(
					D3DXVECTOR3(0,0,deltaMove));
			if (turn)
			{
				currentAngle = deltaAngle;
				countAngle += deltaAngle;
				if (countAngle > maxAngle) turn = false;
			}
			else
			{
				currentAngle = -deltaAngle;
				countAngle -= deltaAngle;

				if (countAngle < minAngle) turn = true;
			}
			model[2]->GetTransform()->RotateSelf(
				currentAngle, 0, 0);
			model[3]->GetTransform()->RotateSelf(
				-currentAngle, 0, 0);
			model[4]->GetTransform()->RotateSelf(
				-currentAngle, 0, 0);
			model[5]->GetTransform()->RotateSelf(
				currentAngle, 0, 0);
		}
		
	}
}

void Scene_01::Render()
{
	for (int i = 0; i < 6; i++)
		model[i]->Render();
}
