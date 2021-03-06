#pragma once

#define FEPSLON 0.00001f

#define FLOATQUAL(a, b) (abs((a) - (b)) < FEPSLON)

#define FLOATZERO(a) (abs(a) < FEPSLON)

#define VECTORZERO(v) (FLOATZERO((v).x) && FLOATZERO((v).y) && FLOATZERO((v).z))

namespace Util
{
	POINT GetMousePos();

	void SetMousePos(int x, int y);

	float Clamp(float value, float min, float max);

	float Clap01(float value);

	float ClapMinusOnePlusOne(float value);

}
