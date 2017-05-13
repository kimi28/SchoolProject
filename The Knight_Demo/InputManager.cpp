#include "InputManager.h"
#include "DrawImage.h"
#include <conio.h>

InputManager::InputManager()
{
	this->drawImage = new DrawImage();
}


InputManager::~InputManager()
{
	delete drawImage;
}

void InputManager::Info(SceneManager * sceneManager)
{
	sceneManager->AddImage(drawImage);

	sceneManager->SetPosition(drawImage);

	sceneManager->ReDraw(drawImage, 4);
}

void InputManager::Input(SceneManager* sceneManager)
{	
	char key = getch();

	switch (key) {
	case 'w':
	case'W':
		if (number > 2) {
			number = 0;
		}
		sceneManager->MoveUp(drawImage, number);
		sceneManager->ReDraw(drawImage, number + 6);
		number++;
		break;
	case 's':
	case 'S':
		if (number > 2) {
			number = 0;
		}
		sceneManager->MoveDown(drawImage, number);
		sceneManager->ReDraw(drawImage, number + 3);
		number++;
		break;
	case 'a':
	case 'A':
		if (number > 2) {
			number = 0;
		}
		sceneManager->MoveLeft(drawImage, number);
		sceneManager->ReDraw(drawImage, number + 12);
		number++;
		break;
	case 'd':
	case 'D':
		if (number > 2) {
			number = 0;
		}
		sceneManager->MoveRight(drawImage, number);
		sceneManager->ReDraw(drawImage, number + 9);
		number++;
		break;
	}
}

void InputManager::InputDungeon(SceneManager* sceneManager)
{
	char key = getch();

	switch (key) {
	case 'w':
	case'W':
		if (number > 2) {
			number = 0;
		}
		sceneManager->MoveUp(drawImage, number);
		sceneManager->ReDrawDungeon(drawImage, number + 6);
		number++;
		break;
	case 's':
	case 'S':
		if (number > 2) {
			number = 0;
		}
		sceneManager->MoveDown(drawImage, number);
		sceneManager->ReDrawDungeon(drawImage, number + 3);
		number++;
		break;
	case 'a':
	case 'A':
		if (number > 2) {
			number = 0;
		}
		sceneManager->MoveLeft(drawImage, number);
		sceneManager->ReDrawDungeon(drawImage, number + 12);
		number++;
		break;
	case 'd':
	case 'D':
		if (number > 2) {
			number = 0;
		}
		sceneManager->MoveRight(drawImage, number);
		sceneManager->ReDrawDungeon(drawImage, number + 9);
		number++;
		break;
	}
}