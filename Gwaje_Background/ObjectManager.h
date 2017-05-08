#pragma once
#include "Character.h"

class ObjectManager
{
private:
	Character* player = new Character();
	Character* monster = new Character();

public:
	ObjectManager();
	~ObjectManager();

	void Update();

};

