#pragma once
#include "Transform.h"
#include "../Manager/SingletonBase.h"
class Camera : public Transform ,public SingletonBase<Camera>
{
public:
	Camera();
	~Camera();
};

