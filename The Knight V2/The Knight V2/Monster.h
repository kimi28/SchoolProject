#include "ObjectBase.h"
#include <vector>
#pragma once

class Monster : public ObjectBase
{
private:
	std::vector<Image*> imageList;
	void AddImage(WCHAR* path);

	int currentImageIndex;
public:
	Monster();
	~Monster();
};

