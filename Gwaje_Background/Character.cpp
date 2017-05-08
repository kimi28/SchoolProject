#include "Character.h"



Character::Character()
{
}

Character::Character(short id, char * name, char * type, int hp, int attack, int defence, int critical, int luck) 
	: ObjectBase(id, name, type, hp, attack, defence, critical, luck)
{

}


Character::~Character()
{
}

void Character::Attack(Character * character)
{
	character->applyDamage(attack);
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
