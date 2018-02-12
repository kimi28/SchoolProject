#pragma once

#define MAX_KEY_NUM	256

class Input : public SingletonBase<Input>
{
private:
	bool	bDownCheck[MAX_KEY_NUM];
	bool	bUpCheck[MAX_KEY_NUM];

public:
	Input(void);
	~Input(void);

	HRESULT Init(void);
	void Release(void);

	bool GetKey(int VKey);
	bool GetKeyDown(int VKey);
	bool GetKeyUp(int VKey);
};

