#include "InputManager.h"
#include <conio.h>


InputManager::InputManager(SceneManager* sceneManager)
{
	this->sceneManager = sceneManager;
}

InputManager::~InputManager()
{
}

void InputManager::Keyboard()
{
	char key = getch();

	switch (key) {
	case 'w':
	case'W':
		sceneManager->OnKeyUp();
		break;
	case 's':
	case 'S':
		sceneManager->OnKeyDown();
		break;
	case 'a':
	case 'A':
		sceneManager->OnKeyLeft();
		break;
	case 'd':
	case 'D':
		sceneManager->OnKeyRight();
		break;
	case 'm':
	case 'M':
		sceneManager->ChangeBackgournd();
		break;
	}
}
