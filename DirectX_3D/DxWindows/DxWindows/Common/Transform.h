#pragma once
#define	RESET_POSITION	1
#define	RESET_RPTATION	2
#define	RESET_SCALE		4

#define	AXIS_X	0
#define	AXIS_Y	1
#define	AXIS_Z	2

#define	SHAKE_X	1
#define	SHAKE_Y	2
#define	SHAKE_Z	4

class Transform
{
protected:
	union
	{
		struct
		{
			D3DXVECTOR3	axis[3];
		};
		struct
		{
			D3DXVECTOR3	right;
			D3DXVECTOR3	up;
			D3DXVECTOR3	forward;
		};
	};

	D3DXVECTOR3	position;
	D3DXVECTOR3	scale;

	D3DXMATRIX	matFinal;

	bool	bAutoUpdate;

public:
	Transform();
	~Transform();


	void SetAutoUpdate(bool bAuto)
	{
		this->bAutoUpdate = bAuto;
	}
	
	void Reset(int resetFlag = -1);

	void SetWorldPosition(float x, float y, float z);
	void SetWorldPosition(D3DXVECTOR3 pos);

	void SetLocalPosition(float x, float y, float z);
	void SetLocalPosition(D3DXVECTOR3 pos);

	void MovePositionLocal(D3DXVECTOR3 delta);

	void RotateWorld(float angleX, float angleY, float angleZ);

	void UpdateTransform();

	D3DXMATRIX GetFinalMatrix();

	D3DXVECTOR3 GetWorldPosition() const;
	D3DXVECTOR3 GetLocalPosition() const;

	void GetUnitAxies(D3DXVECTOR3* vecArr) const;

	void DefaultControl(float timeDelta);


};

