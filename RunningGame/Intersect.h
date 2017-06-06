#pragma once

class DrawRect;
class DrawCircle;
class Intersect
{
public:
	Intersect();
	~Intersect();

	static bool IsContainRect(RECT* rect, DrawRect* comp1, DrawRect* comp2);
	static bool IsPointInCircle(const POINT* point1, const POINT* point2, const float distance);
	static bool IsCircleInRect(const POINT* circle, float radius, const RECT* rect);

private:
};

