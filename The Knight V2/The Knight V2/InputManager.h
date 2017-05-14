#include "SceneManager.h"

#pragma once
class InputManager
{
private:
	SceneManager* sceneManager;
public:
	InputManager(SceneManager* sceneManager);
	~InputManager();
	void Keyboard();
};

