#include "ObjectBase.h"
#include <string.h>

ObjectBase::ObjectBase()
{
}

ObjectBase::ObjectBase(short id, char * name, char * type, int hp, int attack, int defence, int critical, int luck)
{
	this->id = id;
	strcpy(this->name, name);
	strcpy(this->type, type);
	this->hp = hp;
	this->attack = attack;
	this->defence = defence;
	this->critical = critical;
	this->luck = luck;
}


ObjectBase::~ObjectBase()
{
}
