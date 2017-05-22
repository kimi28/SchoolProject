#include "MainCharacter.h"
#include "Monster.h"

#pragma once

const int count = 2;

class WorldManager
{
private:

public:
	WorldManager();
	~WorldManager();

	int GetNextTurn(int currentTurn) {
		currentTurn++;
		if (currentTurn >= count) {
			currentTurn = 0;
		}
		return currentTurn;
	}
	void Attack(MainCharacter* mainCharacter, Monster* monster);
};