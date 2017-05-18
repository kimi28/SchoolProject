#include "Character.h"
#include <vector>
#pragma once

class Monster : public Character
{
private:
	std::vector<Image*> imageList;
	void AddImage(WCHAR* path);

	int currentImageIndex;
public:
	Monster();
	Monster(char* name, int hp, int attack, int defence, int critical, int luck);
	~Monster();

	void Update(int deltaTime);
};

