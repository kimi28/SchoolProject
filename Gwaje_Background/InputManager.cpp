#include "InputManager.h"



InputManager::InputManager(WorldManager* worldManager)
{
	this->worldManager = worldManager;
}


InputManager::~InputManager()
{
}

void InputManager::Start()
{
	// FIXME 启动输入管理线程
}
