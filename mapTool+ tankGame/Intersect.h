#pragma once

class Rect;
class Intersect
{
public:
	Intersect();
	~Intersect();

	static bool IsPointInCircle(const POINT* point1, const POINT* point2, const float distance);
	static bool IsContainRect(RECT* rect, Rect* comp1, Rect* comp2);
	static bool IsPointinRect(POINT * pos, Rect * comp);
	static bool IsCircleInRect(const POINT* circle, float radius, const RECT* rect);
};