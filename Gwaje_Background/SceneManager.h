#include "ObjectManager.h"
#include "DrawImage.h"

#pragma once
class SceneManager
{
private:
	DrawImage* drawImage;
	ObjectManager* objectManager;
public:
	SceneManager(ObjectManager* objectManager);
	~SceneManager();
	void Redraw();
};

