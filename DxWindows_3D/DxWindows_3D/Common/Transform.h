#pragma once
#define RESET_POSITION 1
#define RESET_ROTATION 2
#define RESET_SCALE	   4

#define AXIS_X 0
#define AXIS_Y 1
#define AXIS_Z 2

//ȸ�� �����
#define SHAKE_X 1
#define SHAKE_Y 2
#define SHAKE_Z 4

class Transform
{
protected:
	//�������� union�� ������ axis �迭�� ���� �����ϸ�
	//right, up, forward�ε� ���� ���� �ϴ�.
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

	//��ġ��
	D3DXVECTOR3 position;

	//������ �� 
	D3DXVECTOR3 scale;

	//ȸ�� ���� ���
	D3DXMATRIX matFinal;

	//transform ��ȭ�� �ڵ����� ������Ʈ�� �ɲ���?
	bool bAutoUpdate;

public:
	Transform();
	~Transform();

	//���� ������Ʈ ���� ����
	void SetAutoUpdate(bool bAuto)
	{
		this->bAutoUpdate = bAuto;
	}
	//Transform ������ �ʱ�ȭ
	void Reset(int resetFlag = -1);

	//��ġ�� ���� ��ǥ��� �����Ѵ�. 
	void SetWorldPosition(float x, float y, float z);
	void SetWorldPosition(D3DXVECTOR3 pos);


	//��ġ�� ���� ��ǥ��� �����Ѵ�.  ( �θ� �ִ� ��� ������ �������� ��ġ )
	void SetLocalPosition(float x, float y, float z);
	void SetLocalPosition(D3DXVECTOR3 pos);

	//�θ� �ִ� ��� ���� �������� �̵� ��Ų��.
	void MovePositionLocal(D3DXVECTOR3 delta);

	//������� �̿��� Ư�� ȸ�������� ȸ������ ������
	void RotateWorld(float eAngleX, float eAngleY, float eAngleZ);

	//Trnasform�� ������Ʈ �Ѵ�.
	void UpdateTransform();

	D3DXVECTOR3 GetWorldPosition() const;
	D3DXVECTOR3 GetLocalPosition() const;

	void GetUnitAxis(D3DXVECTOR3* pVecArr) const;

	void DefaultControl(float timeDelta);
};

