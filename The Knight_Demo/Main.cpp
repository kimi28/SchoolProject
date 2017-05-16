#include "InputManager.h"
#include "SceneManager.h"
#include "Vector2D.h"

void main() {
	SceneManager* sceneManager = new SceneManager();
	InputManager* input = new InputManager();

	sceneManager->AddImage();

	sceneManager->SetPositionLobby();

	sceneManager->ReDraw(4);
	
	Sleep(1000);

	while (true) {
		input->ImageInput(sceneManager);
		//input->InputDungeon(sceneManager);
	}

	delete input;
	delete sceneManager;
}