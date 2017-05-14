#include "ObjectBase.h"
#include "Vector2D.h"
#include <vector>

#pragma once
class MainCharacter : public ObjectBase
{
private:
	Vector2D speed;
	std::vector<Image*> imageList;
	void AddImage(WCHAR* path);
	int currentWalkDistance = 0;

	int currentImageIndex;

public:
	MainCharacter();
	~MainCharacter();

	void Move(Vector2D direction);

	 void Update(int deltaTime);
	 void Stop();
};

