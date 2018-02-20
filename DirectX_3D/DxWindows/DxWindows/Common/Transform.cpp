#include "../stdafx.h"
#include "Transform.h"



Transform::Transform()
{
	this->bAutoUpdate = true;

	this->Reset();

	if (this->bAutoUpdate)
		this->UpdateTransform();

}


Transform::~Transform()
{
}

void Transform::Reset(int resetFlag)
{
	if (resetFlag & RESET_POSITION)
	{
		this->position.x = 0;
		this->position.y = 0;
		this->position.z = 0;
	}

	if (resetFlag & RESET_RPTATION)
	{
		//인덱스로 접근
		/*this->axis[0] = D3DXVECTOR3(1, 0, 0);
		this->axis[1] = D3DXVECTOR3(0, 1, 0);
		this->axis[2] = D3DXVECTOR3(0, 0, 1);*/

		//축의 이름으로 접근
		this->right = D3DXVECTOR3(1, 0, 0);
		this->up = D3DXVECTOR3(0, 1, 0);
		this->forward = D3DXVECTOR3(0, 0, 1);
	}

	if (resetFlag & RESET_SCALE)
	{
		this->scale = D3DXVECTOR3(1, 1, 1);
	}

	this->UpdateTransform();

}

void Transform::SetWorldPosition(float x, float y, float z)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(x, y, z);

	this->position.x = pos.x;
	this->position.y = pos.y;
	this->position.z = pos.z;

	if (this->bAutoUpdate)
		this->UpdateTransform();

}

void Transform::SetWorldPosition(D3DXVECTOR3 pos)
{
	this->position.x = pos.x;
	this->position.y = pos.y;
	this->position.z = pos.z;


	if (this->bAutoUpdate)
		this->UpdateTransform();
}

void Transform::SetLocalPosition(float x, float y, float z)
{
}

void Transform::SetLocalPosition(D3DXVECTOR3 pos)
{
}

void Transform::MovePositionLocal(D3DXVECTOR3 delta)
{
	D3DXVECTOR3 move(0, 0, 0);

	D3DXVECTOR3 moveAxis[3];
	this->GetUnitAxies(moveAxis);

	move += moveAxis[0] * delta.x;
	move += moveAxis[1] * delta.y;
	move += moveAxis[2] * delta.z;

	D3DXVECTOR3 nowWorldPos = this->GetWorldPosition();
	this->SetWorldPosition(nowWorldPos + move);


}

void Transform::RotateWorld(float angleX, float angleY, float angleZ)
{
	D3DXQUATERNION quatRot;
	D3DXQuaternionRotationYawPitchRoll
	(
		&quatRot, angleY, angleX, angleZ
	);

	D3DXMATRIX matRotate;
	D3DXMatrixRotationQuaternion
	(
		&matRotate, &quatRot
	);

	this->right = D3DXVECTOR3(1, 0, 0);
	this->up = D3DXVECTOR3(0, 1, 0);
	this->forward = D3DXVECTOR3(0, 0, 1);

	for (int i = 0; i < 3; i++)
		D3DXVec3TransformNormal
		(
			&this->axis[i],
			&this->axis[i],
			&matRotate
		);

	if (this->bAutoUpdate)
		this->UpdateTransform();
}

void Transform::UpdateTransform()
{
	D3DXMatrixIdentity(&this->matFinal);

	D3DXVECTOR3 scaleRight = this->right* scale.x;
	D3DXVECTOR3 scaleUp = this->up * this->scale.y;
	D3DXVECTOR3	scaleForward = this->forward * this->scale.z;

	memcpy(&this->matFinal._11, &scaleRight, sizeof(D3DXVECTOR3));
	memcpy(&this->matFinal._21, &scaleUp, sizeof(D3DXVECTOR3));
	memcpy(&this->matFinal._31, &scaleForward, sizeof(D3DXVECTOR3));
	memcpy(&this->matFinal._41, &this->position, sizeof(D3DXVECTOR3));

}

D3DXMATRIX Transform::GetFinalMatrix()
{
	return matFinal;
}

D3DXVECTOR3 Transform::GetWorldPosition() const
{
	D3DXVECTOR3 pos = this->position;
	return pos;
}

D3DXVECTOR3 Transform::GetLocalPosition() const
{
	return this->position;
}

void Transform::GetUnitAxies(D3DXVECTOR3* vecArr) const
{
	for (int i = 0; i < 3; i++)
		D3DXVec3Normalize(vecArr + i, this->axis + i);
}

void Transform::DefaultControl(float timeDelta)
{
	static float nowAngleH = 0.0f;
	static float nowAngleV = 0.0f;
	static float maxAngleV = 85.0f;
	static float minAngleV = -85.0f;
	static float senitivityH = 0.2f;
	static float senitivityV = 0.2f;
	static D3DXVECTOR3 nowVelocity(0, 0, 0);

	static float accelate = 30.0f;
	static float nowSpeed = 3.0f;
	static float maxSpeed = 10.0f;

	if (INPUT->GetKeyDown(VK_RBUTTON))
	{
		int screenCenterX = WINSIZE_X / 2;
		int screenCenterY = WINSIZE_Y / 2;

		SetMousePos(screenCenterX, screenCenterY);
	}
	else if (INPUT->GetKey(VK_RBUTTON))
	{
		D3DXVECTOR3 inputVector(0, 0, 0);

		if (INPUT->GetKey(VK_UP))
			inputVector.z = 1.0f;
		else if (INPUT->GetKey(VK_DOWN))
			inputVector.z = -1.0f;

		if (INPUT->GetKey(VK_RIGHT))
			inputVector.x = 1.0f;
		else if (INPUT->GetKey(VK_LEFT))
			inputVector.x = -1.0f;

		if (INPUT->GetKey(VK_ACCEPT))
			inputVector.y = 1.0f;
		else if (INPUT->GetKey(VK_OEM_COMMA))
			inputVector.y = -1.0f;

		if (VECTORZERO(inputVector) == false)
			D3DXVec3Normalize(&inputVector, &inputVector);

		D3DXVECTOR3 target = inputVector * maxSpeed;

		this->MovePositionLocal(target*timeDelta);

		int screenCenterX = WINSIZE_X / 2;
		int screenCenterY = WINSIZE_Y / 2;

		POINT mousePos = GetMousePos();

		float deltaX = mousePos.x - screenCenterX;
		float deltaY = mousePos.y - screenCenterY;

		nowAngleH += deltaX * senitivityH;
		nowAngleV += deltaY * senitivityV;

		nowAngleV = Clamp(nowAngleV, minAngleV, maxAngleV);

		SetMousePos(screenCenterX, screenCenterY);

		this->RotateWorld(nowAngleV * ONE_RAD, nowAngleH* ONE_RAD, 0.0f);
	}

}
