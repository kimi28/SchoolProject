#pragma once
#include "SceneManager.h"


class InputManager
{
	int number = 0;

public:
	InputManager();
	~InputManager();

	void LobbyInput(SceneManager* sceneManager);
	void DungeonInput(SceneManager* sceneManager);
};

