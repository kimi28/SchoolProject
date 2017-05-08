#include <stdlib.h>
#include "ObjectBase.h"
#pragma once
class Character :
	public ObjectBase
{
public:
	Character();
	Character(short id, char* name, char* type, int hp, int attack, int defence, int critical, int luck);
	~Character();
	
	int GetHp() { return hp; }
	bool GetDead() { return hp <= 0; }
	char* GetName() { return name; }
	int Getluck() { return luck; }
	int GetCritical() { return critical; }
	int GetAttack() { return attack; }
	void Attack(Character* character);
	void applyDamage(int attack);
	bool isLucky(int prob) {
		int random = rand() % 10000 + 1;
		return random <= prob;
	}
	
};

