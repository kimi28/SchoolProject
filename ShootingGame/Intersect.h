#pragma once

class DrawRect;
class Intersect
{
public:
	Intersect();
	~Intersect();

	static bool IsContainRect(RECT* rect, DrawRect* comp1, DrawRect* comp2);
private:
};

