#include "Character.h"
#include <string.h>



Character::Character()
{
}

Character::Character(char * name, int hp, int attack, int defence, int critical, int luck)
{
	strcpy(this->name, name);
	this->hp = hp;
	this->attack = attack;
	this->defence = defence;
	this->critical = critical;
	this->luck = luck;
}


Character::~Character()
{
}

void Character::applyDamage(int attack)
{
	bool isMiss = isLucky(this->luck);
	bool isCritical = isLucky(this->critical);
	int damage = attack * 120 / (100 + this->defence);

	if (isMiss == false) {
		if (isCritical) {
			damage = damage*1.5;
		}
		hp -= damage;

		if (hp < 0) hp = 0;
	}
}
