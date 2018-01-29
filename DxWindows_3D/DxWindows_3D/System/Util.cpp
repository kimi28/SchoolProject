#include "../stdafx.h"
#include "Util.h"



namespace Util
{
	POINT GetMousePos()
	{
		POINT mousePos;
		GetCursorPos(&mousePos);

		ScreenToClient(g_hWnd, &mousePos);

		return mousePos;
	}
	void SetMousePos(int x, int y)
	{
		POINT setMousePos;
		setMousePos.x = x;
		setMousePos.y = y;

		ClientToScreen(g_hWnd, &setMousePos);

		SetCursorPos(setMousePos.x, setMousePos.y);

	}

	float Clamp(float value, float min, float max)
	{
		if (value < min)
			return min;
		else if (value > max)
			return max;

		return value;

	}
	float Clamp01(float value)
	{
		return Clamp(value, 0, 1);
	}
	float ClampMinusOnePlusOne(float value)
	{
		return Clamp(value, -1, 1);
	}

};