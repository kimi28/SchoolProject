#include "WorldManager.h"

#pragma once
class InputManager
{
private:
	WorldManager* worldManager;
public:
	InputManager(WorldManager* worldManager);
	~InputManager();

	void Start();
};

