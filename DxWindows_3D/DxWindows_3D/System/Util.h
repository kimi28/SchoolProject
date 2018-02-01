#pragma once

#define FEPSLON		0.00001f

//a 와 b 가 같냐?
#define FLOATQUAL(a, b)     (abs((a)- (b)) <FEPSLON)

//a 가 0이냐?
#define FLOATZERO(a)		(abs(a) < FEPSLON)

//제로 벡터 이냐?
#define VECTORZERO(v)		(FLOATZERO((v).x) && FLOATZERO((v).y)&& FLOATZERO((v).z))


namespace Util
{
	POINT GetMousePos();
	void SetMousePos(int x, int y);

	float Clamp(float value, float min, float max);
	float Clamp01(float value);
	float ClampMinusOnePlusOne(float value);
}