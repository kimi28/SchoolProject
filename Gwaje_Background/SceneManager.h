#include "ObjectManager.h"
#include "DrawImage.h"

#pragma once
class SceneManager
{
private:
	ObjectManager* objectManager;
	DrawImage* drawImage;
public:
	SceneManager(ObjectManager* objectManager);
	~SceneManager();
	void RedrawMap();
	void RedrwaNpc();
};

