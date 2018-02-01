#include "../stdafx.h"
#include "Star.h"
#include "ColorShader.h"



Star::Star(ColorShader * shader)
{
	CreateVertexBuffer();
	CreateIndexBuffer();

	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&view);
	D3DXMatrixIdentity(&projection);
	D3DXMatrixLookAtLH(
		&view,
		&D3DXVECTOR3(0, 0, -20),
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 1, 0));
	D3DXMatrixPerspectiveFovLH(
		&projection,
		(float)D3DX_PI / 4.0f,
		WINSIZE_X / WINSIZE_Y,
		0.1f,
		1000.0f);

	viewport.Width = WINSIZE_X;
	viewport.Height = WINSIZE_Y;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	DEVICECONTEXT->RSSetViewports(1, &viewport);

	this->shader = shader;
	angle = 0.0f;
}

Star::~Star()
{
	SAFE_RELEASE(IndexBuffer);
	SAFE_RELEASE(vertexBuffer);
}

void Star::CreateVertexBuffer()
{
	HRESULT hr;

	vertexCount = 13;
	Vertex* vertex = new Vertex[vertexCount];

	vertex[0].position = D3DXVECTOR3(0, 0, 0.3f);
	vertex[1].position = D3DXVECTOR3(0, 0, -0.3f);

	vertex[2].position = D3DXVECTOR3(0, 1, 0);
	vertex[3].position = D3DXVECTOR3(0.3f, 0.3f, 0);
	vertex[4].position = D3DXVECTOR3(0.8f, 0.3f, 0);
	vertex[5].position = D3DXVECTOR3(0.5f, -0.3f, 0);
	vertex[6].position = D3DXVECTOR3(0.8f, -0.8f, 0);
	vertex[7].position = D3DXVECTOR3(0, -0.3f, 0);

	vertex[8].position = D3DXVECTOR3(-0.8f, -0.8f, 0);
	vertex[9].position = D3DXVECTOR3(-0.5f, -0.3f, 0);
	vertex[10].position = D3DXVECTOR3(-0.8f, 0.3f, 0);
	vertex[11].position = D3DXVECTOR3(-0.3f, 0.3f, 0);
	vertex[12].position = D3DXVECTOR3(0, 1, 0);

	for (int i = 0; i < 13; i++)
	{
		vertex[i].color = D3DXCOLOR(i* 0.1f, i* 0.1f, i* 0.1f, 1.0f);
	}




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

void Star::CreateIndexBuffer()
{
	HRESULT hr;

	indexCount = 60;
	UINT* index = new UINT[indexCount];

	int count = 2;
	for (int i = 0; i < 30; i += 3)
	{
		index[i + 0] = count;
		index[i + 1] = count + 1;
		index[i + 2] = 0;

		index[i + 30] = count + 1;
		index[i + 31] = count;
		index[i + 32] = 1;
		count++;
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

void Star::Update(float timeDelta)
{
	//초당 90도 회전
	angle += 90.0f * ONE_RAD * timeDelta;

	D3DXMATRIX matRotate;
	D3DXMatrixRotationY(&matRotate, angle);

	this->world = matRotate;

	this->world._41 = 2;
	this->world._42 = -2;
}

void Star::Render()
{

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	DEVICECONTEXT->IASetVertexBuffers(
		0, 1, &vertexBuffer, &stride, &offset);
	DEVICECONTEXT->IASetIndexBuffer(
		IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	DEVICECONTEXT->IASetPrimitiveTopology
	(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	shader->SetParameters(world, view, projection);

	shader->Render();
	DEVICECONTEXT->DrawIndexed(indexCount, 0, 0);
}
