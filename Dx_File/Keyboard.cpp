#include "stdafx.h"
#include "Keyboard.h"

Keyboard* Keyboard::instance = NULL;

Keyboard * Keyboard::GetInstance()
{
	if (instance == NULL)
		instance = new Keyboard();

	return instance;
}//�ű���

void Keyboard::DeleteInstance()
{
	SAFE_DELETE(instance);
}//������ ����� ������ �������ش�.

void Keyboard::Update()
{
	memcpy(keyOldState, keyState, sizeof(keyOldState));

	ZeroMemory(keyState, sizeof(keyState));//�ʱ�ȭ�Ѵ�.
	ZeroMemory(keyMap, sizeof(keyMap));//�ʱ�ȭ�Ѵ�.


	GetKeyboardState(keyState);

	for (DWORD i = 0; i < MAX_INPUT_KEY; i++) {
		byte key = keyState[i] & 0x80;//�����ִ°� �˼� �ִ�.
		keyState[i] = key ? 1 : 0;

		int oldState = keyOldState[i];
		int state = keyState[i];

		if (oldState == 0 && state == 1) {
			keyMap[i] = KEY_INPUT_STATUS_DOWN;
		}
		else if (oldState == 1 && state == 0) {
			keyMap[i] = KEY_INPUT_STATUS_UP;
		}
		else if (oldState == 1 && state == 1) {
			keyMap[i] = KEY_INPUT_STATUS_PRESS;
		}
		else {
			keyMap[i] = KEY_INPUT_STATUS_NONE;
		}
	}
}

Keyboard::Keyboard()
{
	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyOldState, sizeof(keyOldState));
	ZeroMemory(keyMap, sizeof(keyMap));
}


Keyboard::~Keyboard()
{

}