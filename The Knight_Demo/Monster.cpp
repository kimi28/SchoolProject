#include "Monster.h"



Monster::Monster()
{
}

Monster::Monster(char * name, int hp, int attack, int defence, int critical, int luck)
	:Character::Character(name, hp, attack, defence, critical, luck)
{
}


Monster::~Monster()
{
}
