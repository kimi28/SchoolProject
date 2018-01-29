#include "../stdafx.h"
#include "Cube.h"
#include "ColorShader.h"



Cube::Cube(ColorShader * shader)
{
	CreateVertexBuffer();
	CreateIndexBuffer();
	CreateRenderState();

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
	angle = D3DXVECTOR3(0, 0, 0);
	position = D3DXVECTOR3(0, 0, 0);

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

	vertexCount = 8;
	Vertex* vertex = new Vertex[vertexCount];

	vertex[0].position = D3DXVECTOR3(-1, 1, -1);
	vertex[1].position = D3DXVECTOR3( 1, 1, -1);
	vertex[2].position = D3DXVECTOR3(-1,-1, -1);
	vertex[3].position = D3DXVECTOR3( 1,-1, -1);

	vertex[4].position = D3DXVECTOR3(-1, 1, 1);
	vertex[5].position = D3DXVECTOR3( 1, 1, 1);
	vertex[6].position = D3DXVECTOR3(-1,-1, 1);
	vertex[7].position = D3DXVECTOR3( 1,-1, 1);

	D3DXCOLOR color = D3DXCOLOR(1, 1, 1, 1);
	for (int i = 0; i < 8; i++)
	{
		color.r -= 0.1f;
		color.g -= 0.1f;
		color.b -= 0.1f;

		vertex[i].color = color;	
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

void Cube::CreateIndexBuffer()
{
	HRESULT hr;

	indexCount = 36;
	UINT* index = new UINT[indexCount];
	
	//정면 
	index[0] = 0;
	index[1] = 1;
	index[2] = 2;
	index[3] = 2;
	index[4] = 1;
	index[5] = 3;

	//우측면 
	index[6] = 1;
	index[7] = 5;
	index[8] = 3;
	index[9] = 3;
	index[10] = 5;
	index[11] = 7;

	//후면
	index[12] = 5;
	index[13] = 4;
	index[14] = 6;
	index[15] = 5;
	index[16] = 6;
	index[17] = 7;

	//좌측
	index[18] = 4;
	index[19] = 0;
	index[20] = 6;
	index[21] = 0;
	index[22] = 2;
	index[23] = 6;

	//윗면
	index[24] = 0;
	index[25] = 4;
	index[26] = 5;
	index[27] = 0;
	index[28] = 5;
	index[29] = 1;

	//아래면
	index[30] = 7;
	index[31] = 6;
	index[32] = 2;
	index[33] = 7;
	index[34] = 2;
	index[35] = 3;

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
	rasterizerBuffer.FillMode = D3D11_FILL_WIREFRAME;
	rasterizerBuffer.CullMode = D3D11_CULL_BACK;
	rasterizerBuffer.DepthClipEnable = true;

	HRESULT hr = DEVICE->CreateRasterizerState
	(&rasterizerBuffer, &wireFrameRender);

	assert(SUCCEEDED(hr));
}

void Cube::Update(float timeDelta)
{
	D3DXMATRIX matRotX;
	D3DXMATRIX matRotY;
	D3DXMATRIX matRotZ;
	D3DXMATRIX matTrans;

	D3DXMatrixTranslation(&matTrans, position.x, position.y, position.z);



	if (INPUT->GetKey('A'))
		angle.y += 0.1f;

	if (INPUT->GetKey('D'))
		angle.y -= 0.1f;

	if (INPUT->GetKey('W'))
		angle.x += 0.1f;

	if (INPUT->GetKey('S'))
		angle.x -= 0.1f;

	if (INPUT->GetKey('Q'))
		angle.z += 0.1f;

	if (INPUT->GetKey('E'))
		angle.z -= 0.1f;

	if (INPUT->GetKey(VK_RIGHT))
	{
		view._41 += 0.1f;
	}
	if (INPUT->GetKey(VK_LEFT))
	{
		view._41 -= 0.1f;
	}
	if (INPUT->GetKey(VK_UP))
	{
		view._43 -= 0.1f;
	}
	if (INPUT->GetKey(VK_DOWN))
	{
		view._43 += 0.1f;
	}
	D3DXMatrixRotationX(&matRotX, angle.x);
	D3DXMatrixRotationY(&matRotY, angle.y);
	D3DXMatrixRotationZ(&matRotZ, angle.z);

	this->world = matRotX * matRotY * matRotZ * matTrans;

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

	shader->SetParameters(world, view, projection);

	shader->Render();
	DEVICECONTEXT->DrawIndexed(indexCount, 0, 0);
}
