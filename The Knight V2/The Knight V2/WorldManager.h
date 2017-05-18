#include "MainCharacter.h"
#include "Monster.h"

#pragma once

const int count = 2;

class WorldManager
{
private:
	MainCharacter* mainCharacter;
	Monster* monster;

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

	void PvE();
};

