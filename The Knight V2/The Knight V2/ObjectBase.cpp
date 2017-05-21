#include "ObjectBase.h"
#include <math.h>

ObjectBase::ObjectBase(SceneManager* sceneManager) : position(0, 0), Circles(0,0)
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

int ObjectBase::GetRadius(Rect rect)
{
	int radius = (int)pow((pow((Circles.X - rect.Width), 2) + pow((Circles.Y - rect.Height), 2)), 0.5f);
	return radius;
}

void ObjectBase::Update(int deltaTime)
{

}