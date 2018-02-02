#pragma once
#define RESET_POSITION 1
#define RESET_ROTATION 2
#define RESET_SCALE	   4

#define AXIS_X 0
#define AXIS_Y 1
#define AXIS_Z 2

//회전 허용축
#define SHAKE_X 1
#define SHAKE_Y 2
#define SHAKE_Z 4

class Transform
{
protected:
	//축정보는 union을 묶여서 axis 배열로 접근 가능하며
	//right, up, forward로도 접근 가능 하다.
	union
	{
		struct {
			D3DXVECTOR3 axis[3];
		};
		struct {
			D3DXVECTOR3 right;
			D3DXVECTOR3 up;
			D3DXVECTOR3 forward;
		};
	};

	//위치값
	D3DXVECTOR3 position;

	//스케일 값 
	D3DXVECTOR3 scale;

	//회종 월드 행렬
	D3DXMATRIX matFinal;

	//transform 변화시 자동으로 업데이트가 될꺼냐?
	bool bAutoUpdate;

	//로컬 행렬 
	D3DXMATRIX matLocal; //부모를 기준으로 한 상대 행렬 
						 //부모가 없으면 matFinal이랑 같다
						 //부모 행렬 (null 이면 부모가 없는애 )
	Transform* pParent;

	//자식 참조 (null 이면 자식이 없는애)
	Transform* pFirstChild;

	//형제 참조
	Transform* pNextSibling;
public:
	Transform();
	~Transform();

	//오토 업데이트 여부 셋팅
	void SetAutoUpdate(bool bAuto)
	{
		this->bAutoUpdate = bAuto;
	}
	//Transform 정보를 초기화
	void Reset(int resetFlag = -1);

	void AddChild(Transform* pNewChild);

	void AttackTo(Transform* pNewParent);

	void ReleaseParent();

	//위치를 월드 좌표계로 셋팅한다. 
	void SetWorldPosition(float x, float y, float z);
	void SetWorldPosition(D3DXVECTOR3 pos);


	//위치를 로컬 좌표계로 셋팅한다.  ( 부모가 있는 경우 무모의 상태적인 위치 )
	void SetLocalPosition(float x, float y, float z);
	void SetLocalPosition(D3DXVECTOR3 pos);

	//자신의 축을 기준으로 이동
	void MovePositionLocal(D3DXVECTOR3 delta);

	//스케일 셋팅
	void SetScale(float x, float y, float z);
	void SetScale(D3DXVECTOR3 scale);

	//스케일링
	void Scaling(float dx, float dy, float dz);
	void Scaling(D3DXVECTOR3 deltaScale);

	void RotateSelf(float angleX, float angleY, float angleZ);

	//사원수를 이용한 특정 회전값으로 회전량을 가져라
	void RotateWorld(float eAngleX, float eAngleY, float eAngleZ);

	//Trnasform을 업데이트 한다.
	void UpdateTransform();

	D3DXMATRIX GetFinalMatrix();

	D3DXVECTOR3 GetWorldPosition() const;
	D3DXVECTOR3 GetLocalPosition() const;

	void GetUnitAxies(D3DXVECTOR3* pVecArr) const;

	void DefaultControl(float timeDelta);
};

