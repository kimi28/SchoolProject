#pragma once
#include "SceneManager.h"


class InputManager
{
public:
	InputManager();
	~InputManager();

	void Input(SceneManager* sceneManager);
	void InputDungeon(SceneManager* sceneManager);
};

