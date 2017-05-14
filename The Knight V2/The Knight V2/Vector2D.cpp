#include "Vector2D.h"
#include <math.h>

#define PI 3.1415926

Vector2D Vector2D::Left(-1, 0);
Vector2D Vector2D::Right(1, 0);
Vector2D Vector2D::Up(0, -1);
Vector2D Vector2D::Down(0, 1);
Vector2D Vector2D::Zero(0, 0);


Vector2D::Vector2D(int x, int y)
{
	this->X = x;
	this->Y = y;
}


Vector2D::~Vector2D()
{
}

double Vector2D::angle(Vector2D v)
{
	double i = (v.X * this->X + v.Y * this->Y) / (v.Length() * this->Length());
	double angle = acos(i);
	angle = angle * 180 / PI;
	return angle;
}

double Vector2D::Length()
{
	return pow(pow(X, 2) + pow(Y, 2), 0.5);
}
