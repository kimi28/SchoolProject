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
	D3DXVECTOR2 delta;
	delta.x = abs(point1->x - point2->x);
	delta.y = abs(point1->y - point2->y);

	float length = sqrt(delta.x * delta.x + delta.y * delta.y);

	if (length > distance)
		return false;

	return true;
}

bool Intersect::IsCircleInRect(const POINT * circle, float radius, const RECT * rect)
{
	bool isCheck = true;
	isCheck &= rect->left <= circle->x;
	isCheck &= rect->right >= circle->x;
	isCheck |= rect->top <= circle->y;
	isCheck &= rect->bottom >= circle->y;

	//if ((rect->left <= circle->x &&rect->right >= circle->x)||
	//    (rect->top <= circle->y && rect->bottom >= circle->y)){
	if(isCheck == true){
		RECT temp = {
		rect->left - radius,
		rect->top - radius,
		rect->right + radius,
		rect->bottom + radius,
		};

		isCheck = true;
		isCheck &= temp.left < circle->x;
		isCheck &= temp.right > circle->x;
		isCheck &= temp.top < circle->y;
		isCheck &= temp.bottom > circle->y;

		return isCheck;
	}
	else {
		POINT temp;
		temp = { rect->left, rect->top };
		if (IsPointInCircle(circle, &temp, radius)) {
			return true;
		}

		temp = { rect->left, rect->bottom };
		if (IsPointInCircle(circle, &temp, radius)) {
			return true;
		}

		temp = { rect->right, rect->top };
		if (IsPointInCircle(circle, &temp, radius)) {
			return true;
		}

		temp = { rect->right, rect->bottom };
		if (IsPointInCircle(circle, &temp, radius)) {
			return true;
		}
	}

	return false;
}