#include "SceneManager.h"
#include "ObjectManager.h"
#include "WorldManager.h"
#include "InputManager.h"
#include "DrawImage.h"
#include <Windows.h>
#include <stdio.h>
#include <conio.h>

bool isRunning = true;

void main() {
	WorldManager* worldManager = new WorldManager(); // 管理世界
	ObjectManager* objectManager = new ObjectManager(); // 管理 物件
	SceneManager* sceneManager = new SceneManager(objectManager); // 绘制
	InputManager* inputManager = new InputManager(worldManager); // 管理输入
	inputManager->Start();

	while (isRunning) {
		//isRunning = false;
		char key = getch();
		sceneManager->RedrawMap();
		switch (key) {
		case 'w':
			//worldManager->Update();
			//objectManager->Update();
			break;
		case 's':
			//worldManager->Update();
			//objectManager->Update();
			break;
		case 'a':
			//worldManager->Update();
			//objectManager->Update();
			break;
		case 'd':
			//worldManager->Update();
			//objectManager->Update();
			break;
		}




	}


	delete sceneManager;
	delete worldManager;
	delete objectManager;
	delete inputManager;

}