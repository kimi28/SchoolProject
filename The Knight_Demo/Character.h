#pragma once
#include <stdlib.h>
#include <time.h>

class Character
{
protected:
	char name[255];
	int hp;
	int attack;
	int defence;
	int critical;
	int luck;
public:
	Character();
	Character(char* name, int hp, int attack, int defence, int critical, int luck);
	~Character();

	void applyDamage(int attack);
	int GetHp() { return hp; }
	bool GetDead() { return hp <= 0; }
	char* GetName() { return name; }
	int GetLuck() { return luck; }
	int GetCritical() { return critical; }
	int GatAttack() { return attack; }
	bool isLucky(int prob) {
		srand(time(NULL));
		int random = rand() % 10000 + 1;
		return random <= prob;
	}
};

