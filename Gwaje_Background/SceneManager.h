#include "ObjectManager.h"

#pragma once
class SceneManager
{
private:
	ObjectManager* objectManager;
public:
	SceneManager(ObjectManager* objectManager);
	~SceneManager();
	void Redraw();
};

