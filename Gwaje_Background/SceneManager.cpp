#include "SceneManager.h"

SceneManager::SceneManager(ObjectManager* objectManager)
{
	this->objectManager = objectManager;
	this->drawImage = new DrawImage();
}


SceneManager::~SceneManager()
{
	delete drawImage;
}

void SceneManager::Redraw()
{
}
