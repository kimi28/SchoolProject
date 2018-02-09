#include "../stdafx.h"
#include "Transform.h"



Transform::Transform()
{
	this->pParent = NULL;
	this->pFirstChild = NULL;
	this->pNextSibling = NULL;

	this->bAutoUpdate = true;

	//���� ����
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
		//��ġ�� 0,0,0
		this->position.x = 0;
		this->position.y = 0;
		this->position.z = 0;
	}
	
	if (resetFlag & RESET_ROTATION)
	{
		//�ε����� ����
		//this->axis[0] = D3DXVECTOR3(1, 0, 0);
		//this->axis[1] = D3DXVECTOR3(0, 1, 0);
		//this->axis[2] = D3DXVECTOR3(0, 0, 1);

		//���� �̸����� ����
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

void Transform::AddChild(Transform * pNewChild)
{
	//�̹� �������� �ʿ� ����.
	if (pNewChild->pParent == this)
		return;

	//
	pNewChild->ReleaseParent();

	//�θ��� ������� ��ǥ������ �����ϱ� ����
	//�θ��� final ������� ���Ѵ�.

	D3DXMATRIX matInvFinal;
	D3DXMatrixInverse(&matInvFinal, NULL, &this->matFinal);

	//�ڽ��� position , axis, scale ����
	D3DXVec3TransformCoord(
		&pNewChild->position, &pNewChild->position,
		&matInvFinal);

	//�� 3�� ��ȯ
	for (int i = 0; i < 3; i++)
		D3DXVec3TransformNormal(
			pNewChild->axis + i,
			pNewChild->axis + i, &matInvFinal);
	//3�࿡ ���� ���� ���� ��´�.
	pNewChild->scale.x = D3DXVec3Length(&pNewChild->right);
	pNewChild->scale.y = D3DXVec3Length(&pNewChild->up);
	pNewChild->scale.z = D3DXVec3Length(&pNewChild->forward);

	//���ο� ���� �θ�� ����.
	pNewChild->pParent = this;

	//���� �ڽĳ��� ������
	Transform* pChild = this->pFirstChild;

	if (pChild == NULL)
	{
		//�Ƚ��ϰ� �߰�
		this->pFirstChild = pNewChild;
		pNewChild->pParent = this;
	}
	//�밡���� ��� ����.
	else
	{
		while (pChild != NULL)
		{
			//���� �� �ڸ��� ã�Ҵٸ�...
			if (pChild->pNextSibling == NULL)
			{
				pChild->pNextSibling = pNewChild;
				pNewChild->pParent = this;
				break;
			}
			pChild = pChild->pNextSibling;
		}
	}
	//������Ʈ 
	this->UpdateTransform();
}

void Transform::AttachTo(Transform * pNewParent)
{
	pNewParent->AddChild(this);
}

void Transform::ReleaseParent()
{
	//�θ� ����?
	if (this->pParent == NULL)
		return;

	//�θ�� ���� ���� ���� �θ���� �ڽĿ��� �����...
	Transform* pChild = this->pParent->pFirstChild;

	//���� �θ��� ù��° �ڽ��̴�?
	if (pChild == this)
	{
		//������ �ڽ��� ù��° �ڽ��� �ȴ�.
		this->pParent->pFirstChild = this->pNextSibling;

		//�������� ���� ���´�.
		this->pNextSibling = NULL;
	}
	else
	{
		while (pChild != NULL)
		{
			//���� �ڽ��� ������ ����?
			if (pChild->pNextSibling == this)
			{
				pChild->pNextSibling = this->pNextSibling;

				this->pNextSibling = NULL;
				break;
			}

			pChild = pChild->pNextSibling;
		}

		//�θ�� ���� �����..
		this->pParent = NULL;

		//�ڽ��� ���� ���� ��ġ�� ���� ������ �ʿ��ϴ�.
		//��¥ ���� ��ġ�� matfinal�� ������ �ִ�.
	}
}

void Transform::SetWorldPosition(float x, float y, float z)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(x, y, z);

	//�θ� �ִٸ� �θ��� ������� ��ġ��...
	if (this->pParent != NULL)
	{
		D3DXMATRIX matInvParentFinal;
		D3DXMatrixInverse(&matInvParentFinal,
			NULL, &this->pParent->matFinal);

		//�� ������ pos�� ����
		D3DXVec3TransformCoord(&pos, &pos, &matInvParentFinal);
	}

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
	//�̵� ���� 
	D3DXVECTOR3 move(0, 0, 0);
	//�ڽ��� �̵� ���� ��´�.
	D3DXVECTOR3 moveAxis[3];
	this->GetUnitAxies(moveAxis);

	move += moveAxis[0] * delta.x;
	move += moveAxis[1] * delta.y;
	move += moveAxis[2] * delta.z;

	//���� �̵�
	D3DXVECTOR3 nowWorldPos = this->GetWorldPosition();

	//�Ʒ��� �Լ����� TransFormUpdate�� �Ͼ
	this->SetWorldPosition(nowWorldPos + move);
}

void Transform::SetScale(float x, float y, float z)
{
	this->scale.x = x;
	this->scale.y = y;
	this->scale.z = z;

	if (this->bAutoUpdate)
		this->UpdateTransform();
}

void Transform::SetScale(D3DXVECTOR3 scale)
{
	this->scale = scale;
	if (this->bAutoUpdate)
		this->UpdateTransform();
}

void Transform::Scaling(float dx, float dy, float dz)
{
	this->scale.x += dx;
	this->scale.y += dy;
	this->scale.z += dz;
	if (this->bAutoUpdate)
		this->UpdateTransform();

}

void Transform::Scaling(D3DXVECTOR3 deltaScale)
{
	this->scale += deltaScale;
	if (this->bAutoUpdate)
		this->UpdateTransform();
}

void Transform::RotateSelf(float angleX, float angleY, float angleZ)
{
	//���࿡ ���� ȸ�� ���
	D3DXMATRIX matRotateX;
	D3DXMatrixRotationAxis(&matRotateX, &this->right, angleX);
	//���࿡ ���� ȸ�� ���
	D3DXMATRIX matRotateY;
	D3DXMatrixRotationAxis(&matRotateY, &this->up, angleY);

	D3DXMATRIX matRotateZ;
	D3DXMatrixRotationAxis(&matRotateZ, &this->forward, angleZ);

	//���� ȸ�� ���

	D3DXMATRIX matRotate =
		matRotateY * matRotateX * matRotateZ;

	for (int i = 0; i < 3; i++)
		D3DXVec3TransformNormal(
			&this->axis[i],
			&this->axis[i],
			&matRotate);
	if (this->bAutoUpdate)
		this->UpdateTransform();
}

void Transform::RotateWorld(float eAngleX, float eAngleY, float eAngleZ)
{
	//����� �غ�
	D3DXQUATERNION quatRot;
	D3DXQuaternionRotationYawPitchRoll(
		&quatRot, eAngleY, eAngleX, eAngleZ);

	//������� ���� ��� �غ�
	D3DXMATRIX matRotate;
	D3DXMatrixRotationQuaternion(
		&matRotate, &quatRot);

	//�θ� �ִٸ� �θ��� ������� ��ġ��...
	if (this->pParent != NULL)
	{
		D3DXMATRIX matInvParentFinal;
		D3DXMatrixInverse(&matInvParentFinal,
			NULL, &this->pParent->matFinal);

		//�θ��� ����Ŀ� ��
		matRotate = matRotate * matInvParentFinal;
	}


	//�� ����
	this->right = D3DXVECTOR3(1, 0, 0);
	this->up = D3DXVECTOR3(0, 1, 0);
	this->forward = D3DXVECTOR3(0, 0, 1);

	//���� ȸ�� ��Ĵ�� ȸ�� ��Ų��.
	for (int i = 0; i < 3; i++)
		D3DXVec3TransformNormal(
			&this->axis[i],
			&this->axis[i], 
			&matRotate);

	if (this->bAutoUpdate)
		this->UpdateTransform();
}

void Transform::UpdateTransform()
{
	//matFinal �ʱ�ȭ
	D3DXMatrixIdentity(&this->matLocal);

	//������ ���� ������
	D3DXVECTOR3 scaledRight = this->right * scale.x;
	D3DXVECTOR3 scaledUp = this->up * this->scale.y;
	D3DXVECTOR3 scaledForward = this->forward * this->scale.z;

	memcpy(&this->matLocal._11, &scaledRight, sizeof(D3DXVECTOR3));
	memcpy(&this->matLocal._21, &scaledUp, sizeof(D3DXVECTOR3));
	memcpy(&this->matLocal._31, &scaledForward, sizeof(D3DXVECTOR3));
	memcpy(&this->matLocal._41, &this->position, sizeof(D3DXVECTOR3));

	//���� ���� ���
	if (this->pParent == NULL)
	{
		this->matFinal = matLocal;
	}
	//�θ� ������ 
	else
	{
		this->matFinal = matLocal * this->pParent->matFinal;
	}
	//�ڽ� ������Ʈ
	Transform* pChild = this->pFirstChild;

	while (pChild != NULL)
	{
		pChild->UpdateTransform();
		pChild = pChild->pNextSibling;
	}
}

D3DMATRIX Transform::GetFinalMatrix()
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

void Transform::GetUnitAxies(D3DXVECTOR3 * pVecArr) const
{
	for (int i = 0; i < 3; i++)
		D3DXVec3Normalize(pVecArr + i, this->axis + i);
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

	//���� �������� ȭ���� �߽�����
	if (INPUT->GetKeyDown(VK_RBUTTON))
	{
		int screenCenterX = WINSIZE_X / 2;
		int screenCenterY = WINSIZE_Y / 2;

		//���콺 ��ǥ�� ȭ���� �߽����� 
		SetMousePos(screenCenterX, screenCenterY);
	}
	//��Ŭ�� �Ҷ��� Default control ����
	else if (INPUT->GetKey(VK_RBUTTON))
	{
		//
		// �̵� ó��
		//

		//�Է� ���� ����
		D3DXVECTOR3 inputVector(0, 0, 0);

		if (INPUT->GetKey('W'))
			inputVector.z = 1.0f;
		else if (INPUT->GetKey('S'))
			inputVector.z = -1.0f;
		if (INPUT->GetKey('A'))
			inputVector.x = -1.0f;
		else if (INPUT->GetKey('D'))
			inputVector.x = 1.0f;
		if (INPUT->GetKey('Q'))
			inputVector.y = 1.0f;
		else if (INPUT->GetKey('E'))
			inputVector.y = -1.0f;

		//���� ���Ͱ� �ƴҶ�
		if (VECTORZERO(inputVector) == false)
			//����ȭ
			D3DXVec3Normalize(&inputVector,&inputVector);
	
		//�̵� �ض�
		D3DXVECTOR3 target = inputVector * maxSpeed;
		this->MovePositionLocal(target*timeDelta);
		//
		//	ȸ��ó��
		//

		//ȭ���� �߽���
		int screenCenterX = WINSIZE_X / 2;
		int screenCenterY = WINSIZE_Y / 2;

		//���� ���콺 ��ġ 
		POINT mousePos = GetMousePos();

		//�̵���( �߾ӿ��� �־��� ��)
		float deltaX = mousePos.x - screenCenterX;
		float deltaY = mousePos.y - screenCenterY;

		//�ޱ� �߰�
		nowAngleH += deltaX * senitivityH;
		nowAngleV += deltaY * senitivityV;

		//�ޱ۰��� min max���� ������ 
		nowAngleV = Clamp(nowAngleV, minAngleV, maxAngleV);

		//�ٽ� ���콺�� ���ͷ�..
		SetMousePos(screenCenterX, screenCenterY);

		this->RotateWorld(nowAngleV * ONE_RAD,
			nowAngleH *ONE_RAD, 0.0f);
	}
}
