#include "ObjectBase.h"

ObjectBase::ObjectBase(SceneManager* sceneManager) : position(0, 0)
{
	this->sceneManager = sceneManager;
}

ObjectBase::~ObjectBase()
{
	delete image;
}

void ObjectBase::SetPosition(int x, int y)
{
	position.X = x;
	position.Y = y;

	this->rect.X = x;
	this->rect.Y = y;
}

void ObjectBase::Update(int deltaTime)
{

}