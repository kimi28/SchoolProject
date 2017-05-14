#include "SceneManager.h"
#include "InputManager.h"

void main() {
	SceneManager *sceneManager = new SceneManager();
	InputManager *inputManager = new InputManager(sceneManager);
	while (true) {
		inputManager->Keyboard();
	}
	delete sceneManager;
	delete inputManager;
}