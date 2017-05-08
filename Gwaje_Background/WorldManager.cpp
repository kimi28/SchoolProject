#include "WorldManager.h"
#include "Character.h"
#include <Windows.h>

WorldManager::WorldManager()
{
}


WorldManager::~WorldManager()
{
}

void WorldManager::Update()
{

}

void WorldManager::Attack(Character* player, Character* monster)
{
	Character* characters[COUNT];
	characters[0] = player;
	characters[1] = monster;

	int currentTurn = 0;

	while (true) {
		Character* currentCharacter = characters[currentTurn];

		int nextTurn = GetNextTurn(currentTurn);
		
		Character* targetCharacter = characters[nextTurn];
		targetCharacter->applyDamage(currentCharacter->GetAttack());

		if (targetCharacter->GetDead()) {
			Sleep(2000);
			
			break;
		}
		else{
			Sleep(1000);
		}
		currentTurn = nextTurn;
	}
}
