#pragma once
#include "Character.h"

class Player :public Character
{
public:
	Player();
	Player(char* name, int hp, int attack, int defence, int critical, int luck);
	~Player();
};

