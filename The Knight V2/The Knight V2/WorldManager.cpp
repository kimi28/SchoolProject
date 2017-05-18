#include "WorldManager.h"
#include "MainCharacter.h"
#include "Monster.h"


WorldManager::WorldManager()
{
	this->mainCharacter = new MainCharacter();//"팔라딘", 2000, 100, 50, 100, 1000
	this->monster = new Monster();//"헐크", 1500, 50, 150, 100, 500
}

void WorldManager::PvE() {
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
			//죽은 이미지 살아지기;

			break;
		}
		else {
			Sleep(1000);
			//계속 진행하기
		}
		currentTurn = nextTurn;
	}

}


WorldManager::~WorldManager()
{
	delete mainCharacter;
	delete monster;
}
