#include "InputManager.h"
#include "SceneManager.h"
#include "DrawImage.h"
#include <conio.h>



InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::Input()
{
	int number = 0;
	SceneManager* sceneManager = new SceneManager();
	DrawImage* drawImage = new DrawImage();

	sceneManager->AddImage(drawImage);

	sceneManager->SetPosition(drawImage);


	Sleep(1000);

	sceneManager->ReDraw(drawImage, 4);

	

	while (true) {
		char key = getch();

		switch (key) {
		case 'w':
			if (number > 2) {
				number = 0;
			}
			sceneManager->MoveUp(drawImage, sceneManager, number);
			number++;
			break;
		case 's':
			if (number > 2) {
				number = 0;
			}
			sceneManager->MoveDown(drawImage, sceneManager, number);
			number++;
			break;
		case 'a':
			if (number > 2) {
				number = 0;
			}
			sceneManager->MoveLeft(drawImage, sceneManager, number);
			number++;
			break;
		case 'd':
			if (number > 2) {
				number = 0;
			}
			sceneManager->MoveRight(drawImage, sceneManager, number);
			number++;
			break;

		}
	}

	delete drawImage;
	delete sceneManager;
}
