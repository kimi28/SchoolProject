#include "ObjectBase.h"


ObjectBase::ObjectBase() : position(0, 0)
{

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