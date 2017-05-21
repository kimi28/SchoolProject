#pragma once
class Vector2D
{
public:
	static Vector2D Left;
	static Vector2D Right;
	static Vector2D Up;
	static Vector2D Down;
	static Vector2D Zero;
	int X;
	int Y;
	Vector2D(int x, int y);
	~Vector2D();
	double angle(Vector2D v);
	double Length();
	Vector2D Add(Vector2D v);
	Vector2D Normalize();
};

