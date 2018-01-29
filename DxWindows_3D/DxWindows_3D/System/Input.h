#pragma once
#include "../Manager/SingletonBase.h"

#define MAX_KEY_NUM	256

class Input : public SingletonBase<Input>
{
private:
	bool			m_bDownCheck[MAX_KEY_NUM];
	bool			m_bUpCheck[MAX_KEY_NUM];

public:
	Input(void);
	~Input(void);

	HRESULT Init(void);
	void Release(void);

	bool GetKey(int nVKey);
	bool GetKeyDown(int nVKey);
	bool GetKeyUp(int nVKey);
};

#define INPUT Input::GetInstance()
