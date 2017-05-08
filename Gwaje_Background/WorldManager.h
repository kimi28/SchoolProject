#pragma once
#define COUNT 2
class Character;
class WorldManager
{
public:
	WorldManager();
	~WorldManager();

	void Update();
	void Attack(Character* player, Character* monster);
	int GetNextTurn(int currentTurn) {
		currentTurn++;
		if (currentTurn >= COUNT) {
			currentTurn = 0;
		}
		return currentTurn;
	}
};

