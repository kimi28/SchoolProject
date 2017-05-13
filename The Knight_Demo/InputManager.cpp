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
		if (number > 2) {
			number = 0;
		}
		sceneManager->MoveUp(number);
		sceneManager->ReDraw(number + 6);
		number++;
		break;
	case 's':
	case 'S':
		if (number > 2) {
			number = 0;
		}
		sceneManager->MoveDown(number);
		sceneManager->ReDraw(number + 3);
		number++;
		break;
	case 'a':
	case 'A':
		if (number > 2) {
			number = 0;
		}
		sceneManager->MoveLeft(number);
		sceneManager->ReDraw(number + 12);
		number++;
		break;
	case 'd':
	case 'D':
		if (number > 2) {
			number = 0;
		}
		sceneManager->MoveRight(number);
		sceneManager->ReDraw(number + 9);
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
		if (number > 2) {
			number = 0;
		}
		sceneManager->MoveUp(number);
		sceneManager->ReDrawDungeon(number + 6);
		number++;
		break;
	case 's':
	case 'S':
		if (number > 2) {
			number = 0;
		}
		sceneManager->MoveDown(number);
		sceneManager->ReDrawDungeon(number + 3);
		number++;
		break;
	case 'a':
	case 'A':
		if (number > 2) {
			number = 0;
		}
		sceneManager->MoveLeft(number);
		sceneManager->ReDrawDungeon(number + 12);
		number++;
		break;
	case 'd':
	case 'D':
		if (number > 2) {
			number = 0;
		}
		sceneManager->MoveRight(number);
		sceneManager->ReDrawDungeon(number + 9);
		number++;
		break;
	}
}