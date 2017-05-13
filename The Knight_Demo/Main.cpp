#include "InputManager.h"
#include "SceneManager.h"

void main() {
	SceneManager* sceneManager = new SceneManager();
	InputManager* input = new InputManager();
	
	input->Info(sceneManager);

	while (true) {
		input->Input(sceneManager);
		//input->InputDungeon(sceneManager);
	}

	delete input;
	delete sceneManager;
}