#include "../stdafx.h"
#include "Cube.h"
#include "ColorShader.h"
#include "../Common/Transform.h"


Cube::Cube(ColorShader * shader)
{
	CreateVertexBuffer();
	CreateIndexBuffer();
	CreateRenderState();

	this->shader = shader;
	angle = D3DXVECTOR3(0, 0, 0);
	position = D3DXVECTOR3(0, 0, 0);

	this->transform = new Transform;

	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&view);
	D3DXMatrixIdentity(&projection);


	TwBar* bar = TWEAKBAR->GetBar();
	TwAddSeparator(bar, "", "");
	TwAddVarRW(bar, "position",
		TW_TYPE_DIR3F, &position, "");
}

Cube::~Cube()
{
	SAFE_RELEASE(IndexBuffer);
	SAFE_RELEASE(vertexBuffer);
	SAFE_RELEASE(wireFrameRender);
}

void Cube::CreateVertexBuffer()
{
	HRESULT hr;

	vertexCount = 24;
	Vertex* vertex = new Vertex[vertexCount];

	Vertex* quad = new Vertex[4];
	quad[0].position = D3DXVECTOR3(-0.5f, -0.5f, -0.5f);
	quad[1].position = D3DXVECTOR3(-0.5f, 0.5f, -0.5f);
	quad[2].position = D3DXVECTOR3(0.5f, 0.5f, -0.5f);
	quad[3].position = D3DXVECTOR3(0.5f, -0.5f, -0.5f);

	D3DXMATRIX matRot;
	D3DXMatrixRotationY(&matRot, -90.0f * ONE_RAD);

	//앞면 복사
	memcpy(vertex, quad, sizeof(Vertex) * 4);
	vertex[0].color = D3DXCOLOR(0.0f, 0.0f, 0.5f, 1.0f);
	vertex[1].color = D3DXCOLOR(0.0f, 0.0f, 0.5f, 1.0f);
	vertex[2].color = D3DXCOLOR(0.0f, 0.0f, 0.5f, 1.0f);
	vertex[3].color = D3DXCOLOR(0.0f, 0.0f, 0.5f, 1.0f);

	//돌릴자 
	for (int i = 0; i < 4; i++)
		D3DXVec3TransformCoord(&quad[i].position,
			&quad[i].position, &matRot);

	//우측면 복사
	memcpy(vertex + 4, quad, sizeof(Vertex) * 4);
	vertex[4].color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	vertex[5].color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	vertex[6].color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	vertex[7].color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	//돌릴자 
	for (int i = 0; i < 4; i++)
		D3DXVec3TransformCoord(&quad[i].position,
			&quad[i].position, &matRot);

	//뒷면 복사
	memcpy(vertex + 8, quad, sizeof(Vertex) * 4);
	vertex[8].color = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	vertex[9].color = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	vertex[10].color = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	vertex[11].color = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

	//돌릴자 
	for (int i = 0; i < 4; i++)
		D3DXVec3TransformCoord(&quad[i].position,
			&quad[i].position, &matRot);

	//왼면 복사
	memcpy(vertex + 12, quad, sizeof(Vertex) * 4);
	vertex[12].color = D3DXCOLOR(0.5f, 0.0f, 0.0f, 1.0f);
	vertex[13].color = D3DXCOLOR(0.5f, 0.0f, 0.0f, 1.0f);
	vertex[14].color = D3DXCOLOR(0.5f, 0.0f, 0.0f, 1.0f);
	vertex[15].color = D3DXCOLOR(0.5f, 0.0f, 0.0f, 1.0f);

	//윗면으로 가기 위한 z축 회전
	D3DXMatrixRotationZ(&matRot, -90.0f* ONE_RAD);

	//돌릴자 
	for (int i = 0; i < 4; i++)
		D3DXVec3TransformCoord(&quad[i].position,
			&quad[i].position, &matRot);

	//왼면 복사
	memcpy(vertex + 16, quad, sizeof(Vertex) * 4);
	vertex[16].color = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	vertex[17].color = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	vertex[18].color = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	vertex[19].color = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

	//아래면으로 가기 위한 z축 회전
	D3DXMatrixRotationZ(&matRot, 180.0f* ONE_RAD);

	//돌릴자 
	for (int i = 0; i < 4; i++)
		D3DXVec3TransformCoord(&quad[i].position,
			&quad[i].position, &matRot);

	//왼면 복사
	memcpy(vertex + 20, quad, sizeof(Vertex) * 4);
	vertex[20].color = D3DXCOLOR(0.0f, 0.5f, 0.0f, 1.0f);
	vertex[21].color = D3DXCOLOR(0.0f, 0.5f, 0.0f, 1.0f);
	vertex[22].color = D3DXCOLOR(0.0f, 0.5f, 0.0f, 1.0f);
	vertex[23].color = D3DXCOLOR(0.0f, 0.5f, 0.0f, 1.0f);

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

	shader->Render();
	DEVICECONTEXT->DrawIndexed(indexCount, 0, 0);
}
