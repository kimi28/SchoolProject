#include "Player.h"



Player::Player()
{
}

Player::Player(char * name, int hp, int attack, int defence, int critical, int luck)
	:Character::Character(name, hp, attack, defence, critical, luck)
{
}


Player::~Player()
{
}
