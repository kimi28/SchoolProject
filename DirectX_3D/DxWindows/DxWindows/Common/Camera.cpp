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

void Camera::Updatematrix()
{
	viewport.Width = WINSIZE_X;
	viewport.Height = WINSIZE_Y;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	DEVICECONTEXT->RSSetViewports(1, &viewport);

	D3DXMatrixPerspectiveFovLH
	(
		&projection,
		this->fov,
		static_cast<float>(WINSIZE_X) / static_cast<float>(WINSIZE_Y),
		this->camNear,
		this->camFar
	);

	D3DXMatrixInverse(&view, NULL, &matFinal);

	this->viewProjection = this->view * this->projection;
}
