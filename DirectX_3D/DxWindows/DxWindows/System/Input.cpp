#include "../stdafx.h"
#include "Input.h"



Input::Input(void)
{
}


Input::~Input(void)
{
}

HRESULT Input::Init(void)
{
	for (int index = 0; index < MAX_KEY_NUM; index++)
	{
		bDownCheck[index] = false;
		bUpCheck[index] = false;
	}
	
	return S_OK;
}

void Input::Release(void)
{
}

bool Input::GetKey(int VKey)
{
	return (GetAsyncKeyState(VKey) & 0x8000);
}

bool Input::GetKeyDown(int VKey)
{
	if (GetAsyncKeyState(VKey) & 0x8000)
	{
		if (bDownCheck[VKey] == false)
		{
			bDownCheck[VKey] = true;
			return true;
		}
	}
	else
	{
		bDownCheck[VKey] = false;
	}

	return false;
}

bool Input::GetKeyUp(int VKey)
{
	if (GetAsyncKeyState(VKey) & 0x8000)
	{
		if (bUpCheck[VKey] == false)
		{
			bUpCheck[VKey] = true;
		}
	}
	else
	{
		if (bUpCheck[VKey])
		{
		bUpCheck[VKey] = false;
		return true;
		}
	}

	return false;
}
