#include "../stdafx.h"
#include "Camera.h"



Camera::Camera()
{
	//기본 화각 설정
	this->fov = 60.0f* ONE_RAD;

	//기본 near
	this->camNear = 0.1f;

	//기본 far
	this->camFar = 1000.0f;
}


Camera::~Camera()
{
}

void Camera::UpdateMatrix()
{
	viewport.Width = WINSIZE_X;
	viewport.Height = WINSIZE_Y;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	DEVICECONTEXT->RSSetViewports(1, &viewport);

	//화각에 의한 projection 행렬 업데이트
	D3DXMatrixPerspectiveFovLH(
		&projection,
		this->fov,
		static_cast<float>(WINSIZE_X)
		/ static_cast<float>(WINSIZE_Y),
		this->camNear,
		this->camFar);

	//뷰행렬은 카메라 월드위치에 대한 역행렬이다
	D3DXMatrixInverse(&view, NULL, &matFinal);

	this->viewProjection = this->view * this->projection;
}
