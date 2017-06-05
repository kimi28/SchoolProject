#include "stdafx.h"
#include "Intersect.h"
#include "DrawRect.h"
#include "DrawCircle.h"



Intersect::Intersect()
{
}


Intersect::~Intersect()
{
}

bool Intersect::IsContainRect(RECT * rect, DrawRect * comp1, DrawRect * comp2)
{
	bool isVertical = false;
	bool isHorizontal = false;

	RECT* rect1 = &comp1->GetRect();
	RECT* rect2 = &comp2->GetRect();

	if (rect1->left <= rect2->right && rect1->right >= rect2->left) {
		isHorizontal = true;

		if (rect != NULL) {
			rect->left = (rect1->left >= rect2->left) ? rect1->left : rect2->left;
			rect->right = (rect1->right <= rect2->right) ? rect1->right : rect2->right;
		}
	}
	if (rect1->top <= rect2->bottom && rect1->bottom >= rect2->top) {
		isVertical = true;

		if (rect != NULL) {
			rect->top = max(rect1->top, rect2->top);
			rect->bottom = min(rect1->bottom, rect2->bottom);
		}
	}

	if (isVertical == true && isHorizontal == true) {
		return true;

		if (rect != NULL) {
			*rect = { 0,0,0,0 };
		}
	}
	return false;
}

bool Intersect::IsPointInCircle(const POINT * point1, const POINT * point2, const float distance)
{
	return false;
}

bool Intersect::IsCricleInRect(const POINT * circle, float radius, const RECT * rect)
{
	return false;
}
