#include "WorldManager.h"
#include "MainCharacter.h"
#include "Monster.h"


WorldManager::WorldManager()
{
	this->mainCharacter = new MainCharacter();//"�ȶ��", 2000, 100, 50, 100, 1000
	this->monster = new Monster();//"��ũ", 1500, 50, 150, 100, 500
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
			//���� �̹��� �������;

			break;
		}
		else {
			Sleep(1000);
			//��� �����ϱ�
		}
		currentTurn = nextTurn;
	}

}


WorldManager::~WorldManager()
{
	delete mainCharacter;
	delete monster;
}
