#pragma once
class ObjectBase
{
protected:
	unsigned short id;
	char name[255];
	char type[255];
	int hp;
	int attack;
	int defence;
	int critical;
	int luck;
public:
	ObjectBase();
	ObjectBase(short id, char* name, char* type, int hp, int attack, int defence, int critical, int luck);
	~ObjectBase();
};

