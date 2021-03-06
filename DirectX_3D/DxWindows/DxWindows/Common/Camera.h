#pragma once
#include "Transform.h"

class Camera : public Transform, public SingletonBase<Camera>
{
protected:
	float fov;
	float camNear;
	float camFar;

	D3DXMATRIX view, projection, viewProjection;

	D3D11_VIEWPORT viewport;

public:
	Camera();
	~Camera();

	void Updatematrix();

	D3DXMATRIX GetViewMatrix()const
	{
		return this->view;
	}
	
	D3DXMATRIX GetProjectionMatrix()const
	{
		return this->projection;
	}

	D3DXMATRIX GetViewProjectionMatrix() const
	{
		return this->viewProjection;
	}

	void SetFov(float fov)
	{
		this->fov = fov;
	}

	float GetFov()
	{
		return this->fov;
	}

};


#define CAMERA	Camera::GetInstance()
