#pragma once
#include "SceneManager.h"


class InputManager
{
	DrawImage* drawImage;
	

public:
	InputManager();
	~InputManager();

	int number = 0;

	void Info(SceneManager* sceneManager);
	void Input(SceneManager* sceneManager);
	void InputDungeon(SceneManager* sceneManager);
};

