#include "SceneManager.h"
#include "ObjectManager.h"
#include "WorldManager.h"
#include "InputManager.h"
#include <Windows.h>

bool isRunning = true;

void main() {
	WorldManager* worldManager = new WorldManager(); // 管理世界
	ObjectManager* objectManager = new ObjectManager(); // 管理 物件
	SceneManager* sceneManager = new SceneManager(objectManager); // 绘制
	InputManager* inputManager = new InputManager(worldManager); // 管理输入
	inputManager->Start();

	while (isRunning) {
		//isRunning = false;
		worldManager->Update();
		objectManager->Update();
		sceneManager->Redraw();
		Sleep(10);
	}


	delete sceneManager;
	delete worldManager;
	delete objectManager;
	delete inputManager;

}