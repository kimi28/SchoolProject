#include "InputManager.h"
#include "SceneManager.h"

void main() {
	SceneManager* sceneManager = new SceneManager();
	InputManager* input = new InputManager();
<<<<<<< HEAD
	if (sceneManager->isCollision() == false) {
		input->Input(sceneManager);
	}
	else {
		input->InputDungeon(sceneManager);
=======
	
	input->Info(sceneManager);

	while (true) {
		input->Input(sceneManager);
		//input->InputDungeon(sceneManager);
>>>>>>> origin/master
	}

	delete input;
	delete sceneManager;
}