#include "InputManager.h"

void main() {
	InputManager* input = new InputManager();
	input->InputLobby();

	delete input;
}