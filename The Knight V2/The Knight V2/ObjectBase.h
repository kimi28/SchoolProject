﻿#include <Windows.h>
#include <gdiplus.h>
#include "Vector2D.h"
#pragma once

using namespace Gdiplus;
class SceneManager;
class ObjectBase
{
protected:
	Image* image;
	Rect rect;
	Vector2D position;
	Vector2D Circles;
	SceneManager* sceneManager;

	void SetImage(Image* image) {
		// 内存泄漏
		this->image = image;
	}

public:
	ObjectBase(SceneManager* sceneManager);
	~ObjectBase();
	void SetPosition(int x, int y);
	Image* GetImage() {
		return this->image;
	}

	Rect GetRect() {
		this->rect.X = position.X;
		this->rect.Y = position.Y;
		return this->rect;
	}

	Vector2D GetPosition() {
		return this->position;
	}

	Vector2D GetCircles(Rect rect) {
		this->Circles.X = rect.Width * 0.5f;
		this->Circles.Y = rect.Height * 0.5f;
		
		return this->Circles;
	}
	int GetRadius(Rect rect, int radius);

	void SetSize(int width, int height) {
		this->rect.Width = width;
		this->rect.Height = height;
	}
	virtual void Update(int deltaTime);
};

