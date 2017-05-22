#include "WorldManager.h"
#include "MainCharacter.h"
#include "Monster.h"


WorldManager::WorldManager()
{
}

void WorldManager::Attack(MainCharacter * mainCharacter, Monster * monster)
{
	Character* character[count];
	character[0] = mainCharacter;
	character[1] = monster;

	int currentTurn = 0;

	while (true) {
		Character *currentCharacter = character[currentTurn];

		int nextTurn = GetNextTurn(currentTurn);

		Character* targetCharacter = character[nextTurn];

		if (targetCharacter->GetDead()) {
			Sleep(1000);
			printf("GameOver\n");
			break;
		}
		else {
			Sleep(1000);
			currentCharacter->alppyDamage(currentCharacter->GetAttack());
		}
		currentTurn = nextTurn;
	}
}

WorldManager::~WorldManager()
{

}

