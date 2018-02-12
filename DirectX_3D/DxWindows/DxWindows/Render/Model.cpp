#include "../stdafx.h"
#include "Model.h"
#include "ColorShader.h"



Model::Model(ColorShader* shader)
{
	CreateVertexBuffer();
	CreateIndexBuffer();

	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&view);
	D3DXMatrixIdentity(&projection);

	D3DXMatrixLookAtLH
	(
		&view,
		&D3DXVECTOR3(0, 0, -20),
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 1, 0)
	);
	D3DXMatrixPerspectiveFovLH
	(
		&projection,
		(float)D3DX_PI / 4.0f,
		WINSIZE_X / WINSIZE_Y,
		0.1f,
		1000.0f
	);

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


Model::~Model()
{
	SAFE_RELEASE(indexBuffer);
	SAFE_RELEASE(vertexBuffer);
}

void Model::CreateVertexBuffer()
{
	HRESULT hr;

	vertexCount = 4;
	Vertex* vertex = new Vertex[vertexCount];

	vertex[0].position = D3DXVECTOR3(-1, 1, 0);
	vertex[1].position = D3DXVECTOR3(1, 1, 0);
	vertex[2].position = D3DXVECTOR3(-1, -1, 0);
	vertex[3].position = D3DXVECTOR3(1, -1, 0);

	vertex[0].color = D3DXCOLOR(1, 0, 0, 1);
	vertex[1].color = D3DXCOLOR(0, 1, 0, 1);
	vertex[2].color = D3DXCOLOR(0, 0, 1, 1);
	vertex[3].color = D3DXCOLOR(1, 1, 0, 1);

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

void Model::CreateIndexBuffer()
{
	HRESULT hr;

	indexCount = 6;
	UINT* index = new UINT[indexCount];
	index[0] = 0;
	index[1] = 1;
	index[2] = 2;

	index[3] = 2;
	index[4] = 1;
	index[5] = 3;

	D3D11_BUFFER_DESC desc = { 0 };
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(UINT) * indexCount;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA data = { 0 };
	data.pSysMem = index;

	hr = DEVICE->CreateBuffer(&desc, &data, &indexBuffer);
	assert(SUCCEEDED(hr));

	SAFE_DELETE_ARRAY(index);

}

void Model::Update(float timeDelta)
{
	angle += 90.0f * ONE_RAD * timeDelta;

	D3DXMATRIX matRotate;
	D3DXMatrixRotationY(&matRotate, angle);

	this->world = matRotate;

	this->world._41 = 2;
	this->world._42 = -2;
}

void Model::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	DEVICECONTEXT->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DEVICECONTEXT->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	DEVICECONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	shader->SetParameters(world, view, projection);

	shader->Render();
	DEVICECONTEXT->DrawIndexed(indexCount, 0, 0);
}
