#include "../stdafx.h"
#include "Model.h"
#include "ColorShader.h"
#include "TextureShader.h"



Model::Model(TextureShader * shader)
{
	CreateVertexBuffer();
	CreateIndexBuffer();

	D3DXMatrixIdentity(&world);

	HRESULT hr;
	hr = D3DX11CreateShaderResourceViewFromFile
	(
		DEVICE,
		L"./Textures/Box.png",
		NULL,
		NULL,
		&texture,
		NULL
	);

	
	this->shader = shader;
	angle = 0.0f;
}

Model::~Model()
{
	SAFE_RELEASE(IndexBuffer);
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

	vertex[0].uv = D3DXVECTOR2(0,0);
	vertex[1].uv = D3DXVECTOR2(1,0);
	vertex[3].uv = D3DXVECTOR2(0,1);
	vertex[2].uv = D3DXVECTOR2(1,1);

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

	hr = DEVICE->CreateBuffer(&desc, &data, &IndexBuffer);
	assert(SUCCEEDED(hr));

	SAFE_DELETE_ARRAY(index);
}

void Model::Update(float timeDelta)
{
	//초당 90도 회전
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

	DEVICECONTEXT->IASetVertexBuffers(
		0, 1, &vertexBuffer, &stride, &offset);
	DEVICECONTEXT->IASetIndexBuffer(
		IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	DEVICECONTEXT->IASetPrimitiveTopology
	(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	view = CAMERA->GetViewMatrix();
	projection = CAMERA->GetProjectionMatrix();

	shader->SetParameters(world, view, projection);
	DEVICECONTEXT->PSSetShaderResources(0, 1, &texture);
	shader->Render();
	DEVICECONTEXT->DrawIndexed(indexCount, 0, 0);
}
