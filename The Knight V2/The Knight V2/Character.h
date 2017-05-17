#include "ObjectBase.h"
#pragma once

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
	Character(char* name, int hp, int attack, int defence, int critical, int luck);
	~Character();
};

