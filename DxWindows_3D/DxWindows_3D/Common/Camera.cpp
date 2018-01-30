#include "../stdafx.h"
#include "Camera.h"



Camera::Camera()
{
	this->fov = 60.0f * ONE_RAD;

	this->camNear = 0.1f;

	this->camFar = 1000.0f;
}


Camera::~Camera()
{
}

void Camera::UpdateMatrix()
{
	D3DXMatrixPerspectiveLH
	(
		&projection,
		this->fov,
		static_cast<float>(WINSIZE_X) /
		static_cast<float>(WINSIZE_Y),
		this->camNear,
		this->camFar
	);
	D3DXMatrixInverse(&view, NULL, &matFinal);

	this->viewProjection = this->view * this->projection;
}
