#pragma once
#include "Character.h"

class Monster: public Character
{
public:
	Monster();
	Monster(char* name, int hp, int attack, int defence, int critical, int luck);
	~Monster();
};

