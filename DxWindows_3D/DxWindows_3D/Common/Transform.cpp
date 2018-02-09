#include "../stdafx.h"
#include "Transform.h"



Transform::Transform()
{
	this->pParent = NULL;
	this->pFirstChild = NULL;
	this->pNextSibling = NULL;

	this->bAutoUpdate = true;

	//정보 리셋
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
		//위치는 0,0,0
		this->position.x = 0;
		this->position.y = 0;
		this->position.z = 0;
	}
	
	if (resetFlag & RESET_ROTATION)
	{
		//인덱스로 접근
		//this->axis[0] = D3DXVECTOR3(1, 0, 0);
		//this->axis[1] = D3DXVECTOR3(0, 1, 0);
		//this->axis[2] = D3DXVECTOR3(0, 0, 1);

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

void Transform::AddChild(Transform * pNewChild)
{
	//이미 내새끼면 필요 없다.
	if (pNewChild->pParent == this)
		return;

	//
	pNewChild->ReleaseParent();

	//부모의 상대적인 좌표값으로 갱신하기 위해
	//부모의 final 역행렬을 구한다.

	D3DXMATRIX matInvFinal;
	D3DXMatrixInverse(&matInvFinal, NULL, &this->matFinal);

	//자식의 position , axis, scale 갱신
	D3DXVec3TransformCoord(
		&pNewChild->position, &pNewChild->position,
		&matInvFinal);

	//축 3개 변환
	for (int i = 0; i < 3; i++)
		D3DXVec3TransformNormal(
			pNewChild->axis + i,
			pNewChild->axis + i, &matInvFinal);
	//3축에 대한 길이 값을 얻는다.
	pNewChild->scale.x = D3DXVec3Length(&pNewChild->right);
	pNewChild->scale.y = D3DXVec3Length(&pNewChild->up);
	pNewChild->scale.z = D3DXVec3Length(&pNewChild->forward);

	//새로운 놈의 부모는 나다.
	pNewChild->pParent = this;

	//나의 자식놈의 포인터
	Transform* pChild = this->pFirstChild;

	if (pChild == NULL)
	{
		//안심하고 추가
		this->pFirstChild = pNewChild;
		pNewChild->pParent = this;
	}
	//대가족에 들어 간다.
	else
	{
		while (pChild != NULL)
		{
			//내가 들어갈 자리를 찾았다면...
			if (pChild->pNextSibling == NULL)
			{
				pChild->pNextSibling = pNewChild;
				pNewChild->pParent = this;
				break;
			}
			pChild = pChild->pNextSibling;
		}
	}
	//업데이트 
	this->UpdateTransform();
}

void Transform::AttachTo(Transform * pNewParent)
{
	pNewParent->AddChild(this);
}

void Transform::ReleaseParent()
{
	//부모가 없니?
	if (this->pParent == NULL)
		return;

	//부모랑 연을 끊기 전에 부모부터 자식연을 끊어라...
	Transform* pChild = this->pParent->pFirstChild;

	//내가 부모의 첫번째 자식이니?
	if (pChild == this)
	{
		//내다음 자식이 첫번째 자식이 된다.
		this->pParent->pFirstChild = this->pNextSibling;

		//형재들과의 연도 끊는다.
		this->pNextSibling = NULL;
	}
	else
	{
		while (pChild != NULL)
		{
			//현재 자식의 다음이 나니?
			if (pChild->pNextSibling == this)
			{
				pChild->pNextSibling = this->pNextSibling;

				this->pNextSibling = NULL;
				break;
			}

			pChild = pChild->pNextSibling;
		}

		//부모랑 연을 끊어라..
		this->pParent = NULL;

		//자신의 현재 월드 위치에 대한 갱신이 필요하다.
		//진짜 월드 위치는 matfinal이 가지고 있다.
	}
}

void Transform::SetWorldPosition(float x, float y, float z)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(x, y, z);

	//부모가 있다면 부모의 상대적인 위치로...
	if (this->pParent != NULL)
	{
		D3DXMATRIX matInvParentFinal;
		D3DXMatrixInverse(&matInvParentFinal,
			NULL, &this->pParent->matFinal);

		//그 역행을 pos에 적용
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
	//이동 벡터 
	D3DXVECTOR3 move(0, 0, 0);
	//자신의 이동 축을 얻는다.
	D3DXVECTOR3 moveAxis[3];
	this->GetUnitAxies(moveAxis);

	move += moveAxis[0] * delta.x;
	move += moveAxis[1] * delta.y;
	move += moveAxis[2] * delta.z;

	//월드 이동
	D3DXVECTOR3 nowWorldPos = this->GetWorldPosition();

	//아래의 함수에서 TransFormUpdate가 일어남
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
	//각축에 대한 회전 행렬
	D3DXMATRIX matRotateX;
	D3DXMatrixRotationAxis(&matRotateX, &this->right, angleX);
	//각축에 대한 회전 행렬
	D3DXMATRIX matRotateY;
	D3DXMatrixRotationAxis(&matRotateY, &this->up, angleY);

	D3DXMATRIX matRotateZ;
	D3DXMatrixRotationAxis(&matRotateZ, &this->forward, angleZ);

	//최종 회전 행렬

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
	//사원수 준비
	D3DXQUATERNION quatRot;
	D3DXQuaternionRotationYawPitchRoll(
		&quatRot, eAngleY, eAngleX, eAngleZ);

	//사원수에 의한 행렬 준비
	D3DXMATRIX matRotate;
	D3DXMatrixRotationQuaternion(
		&matRotate, &quatRot);

	//부모가 있다면 부모의 상대적인 위치로...
	if (this->pParent != NULL)
	{
		D3DXMATRIX matInvParentFinal;
		D3DXMatrixInverse(&matInvParentFinal,
			NULL, &this->pParent->matFinal);

		//부모의 역행렬에 곱
		matRotate = matRotate * matInvParentFinal;
	}


	//축 리셋
	this->right = D3DXVECTOR3(1, 0, 0);
	this->up = D3DXVECTOR3(0, 1, 0);
	this->forward = D3DXVECTOR3(0, 0, 1);

	//최종 회전 행렬대로 회전 시킨다.
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
	//matFinal 초기화
	D3DXMatrixIdentity(&this->matLocal);

	//스케일 먹은 축정보
	D3DXVECTOR3 scaledRight = this->right * scale.x;
	D3DXVECTOR3 scaledUp = this->up * this->scale.y;
	D3DXVECTOR3 scaledForward = this->forward * this->scale.z;

	memcpy(&this->matLocal._11, &scaledRight, sizeof(D3DXVECTOR3));
	memcpy(&this->matLocal._21, &scaledUp, sizeof(D3DXVECTOR3));
	memcpy(&this->matLocal._31, &scaledForward, sizeof(D3DXVECTOR3));
	memcpy(&this->matLocal._41, &this->position, sizeof(D3DXVECTOR3));

	//나의 최종 행렬
	if (this->pParent == NULL)
	{
		this->matFinal = matLocal;
	}
	//부모가 있으면 
	else
	{
		this->matFinal = matLocal * this->pParent->matFinal;
	}
	//자식 업데이트
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

	//최초 누를때는 화면의 중심으로
	if (INPUT->GetKeyDown(VK_RBUTTON))
	{
		int screenCenterX = WINSIZE_X / 2;
		int screenCenterY = WINSIZE_Y / 2;

		//마우스 좌표을 화면의 중심으로 
		SetMousePos(screenCenterX, screenCenterY);
	}
	//우클릭 할때만 Default control 동작
	else if (INPUT->GetKey(VK_RBUTTON))
	{
		//
		// 이동 처리
		//

		//입력 방향 벡터
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

		//제로 벡터가 아닐때
		if (VECTORZERO(inputVector) == false)
			//정규화
			D3DXVec3Normalize(&inputVector,&inputVector);
	
		//이동 해라
		D3DXVECTOR3 target = inputVector * maxSpeed;
		this->MovePositionLocal(target*timeDelta);
		//
		//	회전처리
		//

		//화면의 중심점
		int screenCenterX = WINSIZE_X / 2;
		int screenCenterY = WINSIZE_Y / 2;

		//현재 마우스 위치 
		POINT mousePos = GetMousePos();

		//이동량( 중앙에서 멀어진 량)
		float deltaX = mousePos.x - screenCenterX;
		float deltaY = mousePos.y - screenCenterY;

		//앵글 추가
		nowAngleH += deltaX * senitivityH;
		nowAngleV += deltaY * senitivityV;

		//앵글값을 min max범위 안으로 
		nowAngleV = Clamp(nowAngleV, minAngleV, maxAngleV);

		//다시 마우스는 센터로..
		SetMousePos(screenCenterX, screenCenterY);

		this->RotateWorld(nowAngleV * ONE_RAD,
			nowAngleH *ONE_RAD, 0.0f);
	}
}
