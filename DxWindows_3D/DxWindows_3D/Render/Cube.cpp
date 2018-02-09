#include "../stdafx.h"
#include "Cube.h"
#include "ColorShader.h"
#include "TextureShader.h"
#include "../Common/Transform.h"


Cube::Cube(TextureShader * shader)
{
	//CreateVertexBuffer();
	//CreateIndexBuffer();
	//CreateRenderState();

	this->shader = shader;
	angle = D3DXVECTOR3(0, 0, 0);
	position = D3DXVECTOR3(0, 0, 0);

	this->transform = new Transform;

	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&view);
	D3DXMatrixIdentity(&projection);

	HRESULT hr = D3DX11CreateShaderResourceViewFromFile
	(
		DEVICE,
		L"./Textures/KakaoTalk_20161208_150843363.png",
		NULL,
		NULL,
		&texture,
		NULL
	);
}

Cube::~Cube()
{
	SAFE_RELEASE(IndexBuffer);
	SAFE_RELEASE(vertexBuffer);
	SAFE_RELEASE(wireFrameRender);
}

void Cube::CreateVertexBuffer(
	ST_TEXTURE_RANGE stRange, int widthRatio
	,int heightRatio,int depthRatio)
{
	HRESULT hr;

	vertexCount = 24;
	Vertex* vertex = new Vertex[vertexCount];

	Vertex* quad = new Vertex[4];
	quad[0].position = D3DXVECTOR3(-0.5f, -0.5f, -0.5f);
	quad[1].position = D3DXVECTOR3(-0.5f,  0.5f, -0.5f);
	quad[2].position = D3DXVECTOR3( 0.5f,  0.5f, -0.5f);
	quad[3].position = D3DXVECTOR3( 0.5f, -0.5f, -0.5f);

	D3DXMATRIX matRot;
	D3DXMatrixRotationY(&matRot, -90.0f * ONE_RAD);

	//앞면 복사
	memcpy(vertex, quad, sizeof(Vertex) * 4);
	
	//돌릴자 
	for (int i = 0; i < 4; i++)
		D3DXVec3TransformCoord(&quad[i].position,
			&quad[i].position, &matRot);

	//우측면 복사
	memcpy(vertex + 4, quad, sizeof(Vertex) * 4);
	
	//돌릴자 
	for (int i = 0; i < 4; i++)
		D3DXVec3TransformCoord(&quad[i].position,
			&quad[i].position, &matRot);

	//뒷면 복사
	memcpy(vertex + 8, quad, sizeof(Vertex) * 4);
	
	//돌릴자 
	for (int i = 0; i < 4; i++)
		D3DXVec3TransformCoord(&quad[i].position,
			&quad[i].position, &matRot);

	//왼면 복사
	memcpy(vertex + 12, quad, sizeof(Vertex) * 4);
	
	//윗면으로 가기 위한 z축 회전
	D3DXMatrixRotationZ(&matRot, -90.0f* ONE_RAD);

	//돌릴자 
	for (int i = 0; i < 4; i++)
		D3DXVec3TransformCoord(&quad[i].position,
			&quad[i].position, &matRot);

	//왼면 복사
	memcpy(vertex + 16, quad, sizeof(Vertex) * 4);
	
	//아래면으로 가기 위한 z축 회전
	D3DXMatrixRotationZ(&matRot, 180.0f* ONE_RAD);

	//돌릴자 
	for (int i = 0; i < 4; i++)
		D3DXVec3TransformCoord(&quad[i].position,
			&quad[i].position, &matRot);

	//왼면 복사
	memcpy(vertex + 20, quad, sizeof(Vertex) * 4);
	
	enum
	{
		E_BACK,
		E_RIGHT,
		E_FRONT,
		E_LEFT,
		E_TOP,
		E_BOTTOM,
		E_COUNT
	};

	// int nWidthRatio /*= 1*/ 

	float fRangeWidth = stRange.vMax.x - stRange.vMin.x;
	float fRangeHeight = stRange.vMax.y - stRange.vMin.y;

	float fTexUnitWidth = 1.0f / 16.0f;
	float fTexUnitHeight = 1.0f / 8.0f;

	float fHalfRangeWidth = fRangeWidth / 2.0f;

	ST_TEXTURE_RANGE stFaceRange[E_COUNT];


	// 초기화
	stFaceRange[E_TOP].vMin = stRange.vMin;
	stFaceRange[E_TOP].vMax = stRange.vMin;

	// 누적 가산
	stFaceRange[E_TOP].vMin.x += (fHalfRangeWidth - fTexUnitWidth  * widthRatio);
	stFaceRange[E_TOP].vMin.y += 0;
	stFaceRange[E_TOP].vMax.x += fHalfRangeWidth;
	stFaceRange[E_TOP].vMax.y += (fTexUnitHeight * depthRatio);

	stFaceRange[E_BOTTOM] = stFaceRange[E_TOP];
	stFaceRange[E_BOTTOM].vMin.x += (fTexUnitWidth  * widthRatio);
	stFaceRange[E_BOTTOM].vMax.x += (fTexUnitWidth  * widthRatio);

	// 초기화
	stFaceRange[E_RIGHT].vMin = stRange.vMin;
	stFaceRange[E_RIGHT].vMax = stRange.vMin;

	// 누적 가산
	stFaceRange[E_RIGHT].vMin.x += 0;
	stFaceRange[E_RIGHT].vMin.y += (fTexUnitHeight * depthRatio);
	stFaceRange[E_RIGHT].vMax.x += (fTexUnitWidth * depthRatio);
	stFaceRange[E_RIGHT].vMax.y += fRangeHeight;

	stFaceRange[E_FRONT] = stFaceRange[E_RIGHT];
	stFaceRange[E_FRONT].vMin.x += (fTexUnitWidth * depthRatio);
	stFaceRange[E_FRONT].vMax.x += (fTexUnitWidth  *widthRatio);

	stFaceRange[E_LEFT] = stFaceRange[E_FRONT];
	stFaceRange[E_LEFT].vMin.x += (fTexUnitWidth  * widthRatio);
	stFaceRange[E_LEFT].vMax.x += (fTexUnitWidth * depthRatio);

	stFaceRange[E_BACK] = stFaceRange[E_LEFT];
	stFaceRange[E_BACK].vMin.x += (fTexUnitWidth * depthRatio);
	stFaceRange[E_BACK].vMax.x += (fTexUnitWidth  * widthRatio);

	for (int i = 0; i < E_COUNT; i++)
	{
		vertex[i * 4 + 0].uv = D3DXVECTOR2(stFaceRange[i].vMin.x, stFaceRange[i].vMax.y);
		vertex[i * 4 + 1].uv = D3DXVECTOR2(stFaceRange[i].vMin.x, stFaceRange[i].vMin.y);
		vertex[i * 4 + 2].uv = D3DXVECTOR2(stFaceRange[i].vMax.x, stFaceRange[i].vMin.y);
		vertex[i * 4 + 3].uv = D3DXVECTOR2(stFaceRange[i].vMax.x, stFaceRange[i].vMax.y);

	}

	for (int i = 0; i < 24; i++)
		vertex[i].position.y -= 0.5f;

	D3D11_BUFFER_DESC desc = { 0 };
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(Vertex) * vertexCount;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA data = { 0 };
	data.pSysMem = vertex;

	hr = DEVICE->CreateBuffer(&desc, &data, &vertexBuffer);
	assert(SUCCEEDED(hr));

	SAFE_DELETE_ARRAY(vertex);
}

void Cube::CreateIndexBuffer()
{
	HRESULT hr;

	indexCount = 36;
	UINT* index = new UINT[indexCount];
	
	for (int i = 0; i < 6; i++)
	{
		//정점의 스타트 인덱스 
		UINT vertexIndex = i * 4;
		//인덱스 배열의 스타트 인덱스

		int indicexIndex = i * 6;

		index[indicexIndex + 0] = vertexIndex + 0;
		index[indicexIndex + 1] = vertexIndex + 1;
		index[indicexIndex + 2] = vertexIndex + 2;
		index[indicexIndex + 3] = vertexIndex + 0;
		index[indicexIndex + 4] = vertexIndex + 2;
		index[indicexIndex + 5] = vertexIndex + 3;
	}
	

	D3D11_BUFFER_DESC desc = { 0 };
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(UINT) * indexCount;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA data = { 0 };
	data.pSysMem = index;

	hr = DEVICE->CreateBuffer(&desc, &data, &IndexBuffer);
	assert(SUCCEEDED(hr));

	SAFE_DELETE_ARRAY(index);
}

void Cube::CreateRenderState()
{
	D3D11_RASTERIZER_DESC rasterizerBuffer;
	ZeroMemory(&rasterizerBuffer, sizeof(D3D11_RASTERIZER_DESC));
	rasterizerBuffer.FillMode = D3D11_FILL_SOLID;
	rasterizerBuffer.CullMode = D3D11_CULL_BACK;
	rasterizerBuffer.DepthClipEnable = true;

	HRESULT hr = DEVICE->CreateRasterizerState
	(&rasterizerBuffer, &wireFrameRender);

	assert(SUCCEEDED(hr));
}

void Cube::Update(float timeDelta)
{

}

void Cube::Render()
{

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	DEVICECONTEXT->IASetVertexBuffers(
		0, 1, &vertexBuffer, &stride, &offset);
	DEVICECONTEXT->IASetIndexBuffer(
		IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	DEVICECONTEXT->IASetPrimitiveTopology
	(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DEVICECONTEXT->RSSetState(wireFrameRender);
	world = transform->GetFinalMatrix();
	view = CAMERA->GetViewMatrix();
	projection = CAMERA->GetProjectionMatrix();
	shader->SetParameters(world, view, projection);
	DEVICECONTEXT->PSSetShaderResources(0, 1, &texture);

	shader->Render();
	DEVICECONTEXT->DrawIndexed(indexCount, 0, 0);
}
