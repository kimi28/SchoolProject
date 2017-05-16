#include "InputManager.h"

#include <conio.h>

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::ImageInput(SceneManager* sceneManager)
{
	char key = getch();

	switch (key) {
	case 'w':
	case'W':
		if (number > 3) {
			number = 1;
		}
		sceneManager->MoveUp(number);
		sceneManager->ReDraw(number + 3);
		number++;
		break;
	case 's':
	case 'S':
		if (number > 3) {
			number = 1;
		}
		sceneManager->MoveDown(number);
		sceneManager->ReDraw(number);
		number++;
		break;
	case 'a':
	case 'A':
		if (number > 3) {
			number = 1;
		}
		sceneManager->MoveLeft(number);
		sceneManager->ReDraw(number + 9);
		number++;
		break;
	case 'd':
	case 'D':
		if (number > 3) {
			number = 1;
		}
		sceneManager->MoveRight(number);
		sceneManager->ReDraw(number + 6);
		number++;
		break;
	}
}

void InputManager::DungeonInput(SceneManager* sceneManager)
{
	char key = getch();

	switch (key) {
	case 'w':
	case'W':
		if (number > 3) {
			number = 1;
		}
		sceneManager->MoveUp(number);
		sceneManager->ReDrawDungeon(number + 3);
		number++;
		break;
	case 's':
	case 'S':
		if (number > 3) {
			number = 1;
		}
		sceneManager->MoveDown(number);
		sceneManager->ReDrawDungeon(number);
		number++;
		break;
	case 'a':
	case 'A':
		if (number > 3) {
			number = 1;
		}
		sceneManager->MoveLeft(number);
		sceneManager->ReDrawDungeon(number + 9);
		number++;
		break;
	case 'd':
	case 'D':
		if (number > 3) {
			number = 1;
		}
		sceneManager->MoveRight(number);
		sceneManager->ReDrawDungeon(number + 6);
		number++;
		break;
	}
}