#pragma once
#include "SceneManager.h"


class InputManager
{
	

public:
	InputManager();
	~InputManager();

	int number = 0;

	void ImageInput(SceneManager* sceneManager);
	void DungeonInput(SceneManager* sceneManager);
};

