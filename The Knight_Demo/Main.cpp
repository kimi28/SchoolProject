#include "InputManager.h"
#include "SceneManager.h"

void main() {
	SceneManager* sceneManager = new SceneManager();
	InputManager* input = new InputManager();
		input->InputLobby(sceneManager);

	delete input;
	delete sceneManager;
}