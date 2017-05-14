#pragma once
class Vector2D
{
public:
	static Vector2D Left;
	static Vector2D Right;
	static Vector2D Up;
	static Vector2D Down;
	int X;
	int Y;
	Vector2D(int x, int y);
	~Vector2D();
	double angle(Vector2D v);
	double Length();
};

