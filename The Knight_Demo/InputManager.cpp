#include "InputManager.h"
#include "DrawImage.h"
#include <conio.h>

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::InputLobby(SceneManager* sceneManager)
{
	int number = 0;
	DrawImage* drawImage = new DrawImage();

	sceneManager->AddImage(drawImage);

	sceneManager->SetPosition(drawImage);

	Sleep(1000);

	sceneManager->ReDraw(drawImage, 4);

	while (true) {
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
	delete drawImage;
}

void InputManager::InputDungeon(SceneManager * sceneManager)
{
	int number = 0;
	DrawImage* drawImage = new DrawImage();

	sceneManager->AddImage(drawImage);

	sceneManager->SetPositionDungeon(drawImage);

	Sleep(1000);

	sceneManager->ReDrawDungeon(drawImage, 4);

	while (true) {
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
	delete drawImage;
}
