#include "ObjectBase.h"
#pragma once

class SceneManager;
class Character : public ObjectBase
{
private:
	char* name;
	int hp;
	int attack;
	int defence;
	int critical;
	int luck;
public:
	Character(SceneManager* sceneManager);
	Character(SceneManager* sceneManager, char* name, int hp, int attack, int defence, int critical, int luck);
	~Character();

	void alppyDamage(int attack);
	int GetHp() { return hp; }
	bool GetDead() { return hp <= 0; }
	char * GetName() { return name; }
	int GetLuck() { return luck; }
	int GetCritical() { return critical; }
	int GetAttack() { return attack; }
	bool isLucky(int prob) {
		int random = rand() % 10000 + 1;
		return random <= prob;
	}
};

