#include "InputManager.h"
#include "SceneManager.h"

void main() {
	SceneManager* sceneManager = new SceneManager();
	InputManager* input = new InputManager();
	if (sceneManager->isCollision() == false) {
		input->Input(sceneManager);
	}
	else {
		input->InputDungeon(sceneManager);
	}

	delete input;
	delete sceneManager;
}