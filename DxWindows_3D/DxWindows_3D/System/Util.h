#pragma once

#define FEPSLON		0.00001f

//a �� b �� ����?
#define FLOATQUAL(a, b)     (abs((a)- (b)) <FEPSLON)

//a �� 0�̳�?
#define FLOATZERO(a)		(abs(a) < FEPSLON)

//���� ���� �̳�?
#define VECTORZERO(v)		(FLOATZERO((v).x) && FLOATZERO((v).y)&& FLOATZERO((v).z))


namespace Util
{
	POINT GetMousePos();
	void SetMousePos(int x, int y);

	float Clamp(float value, float min, float max);
	float Clamp01(float value);
	float ClampMinusOnePlusOne(float value);

	struct ST_TEXTURE_RANGE
	{
		D3DXVECTOR2 vMin;
		D3DXVECTOR2 vMax;

		ST_TEXTURE_RANGE() :vMin(0, 0), vMax(1, 1) {}
		ST_TEXTURE_RANGE(D3DXVECTOR2 _vMin, D3DXVECTOR2 _vMax) : vMin(_vMin), vMax(_vMax) {}


	};
}