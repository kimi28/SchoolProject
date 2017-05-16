#pragma once
#include "SceneManager.h"


class InputManager
{
	

public:
	InputManager();
	~InputManager();

	int number = 1;

	void ImageInput(SceneManager* sceneManager);
	void DungeonInput(SceneManager* sceneManager);
};

