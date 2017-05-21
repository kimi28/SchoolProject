#include "Character.h"
#include <vector>
#pragma once

class MainCharacter : public Character
{
private:
	Vector2D speed;
	std::vector<Image*> imageList;
	void AddImage(WCHAR* path);
	int currentWalkDistance = 0;

	int currentImageIndex;

public:
	MainCharacter();
	MainCharacter(char* name, int hp, int attack, int defence, int critical, int luck);
	~MainCharacter();

	bool isCollision(Vector2D direction, RECT rect);
	void Move(Vector2D direction);
	void Update(int deltaTime);
	void Stop();

};