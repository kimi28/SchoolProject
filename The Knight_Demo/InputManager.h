#pragma once
#include "SceneManager.h"


class InputManager
{
public:
	InputManager();
	~InputManager();

	void InputLobby(SceneManager* sceneManager);
	void InputDungeon(SceneManager* sceneManager);
};

