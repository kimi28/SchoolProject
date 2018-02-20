#include "../stdafx.h"
#include "Cube.h"
#include "ColorShader.h"
#include "../Common/Transform.h"



Cube::Cube(ColorShader* shader)
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
	TwAddVarRW(bar, "position", TW_TYPE_DIR3F, &position, "");
}


Cube::~Cube()
{
	SAFE_RELEASE(indexBuffer);
	SAFE_RELEASE(vertexBuffer);
	SAFE_RELEASE(wireFrameRender);
}

void Cube::CreateVertexBuffer()
{
	HRESULT hr;

	vertexCount = 8;
	Vertex* vertex = new Vertex[vertexCount];

	vertex[0].position = D3DXVECTOR3(-1, 1, -1);
	vertex[1].position = D3DXVECTOR3(1, 1, -1);
	vertex[2].position = D3DXVECTOR3(-1, -1, -1);
	vertex[3].position = D3DXVECTOR3(1, -1, -1);

	vertex[4].position = D3DXVECTOR3(-1, 1, 1);
	vertex[5].position = D3DXVECTOR3(1, 1, 1);
	vertex[6].position = D3DXVECTOR3(-1, -1, 1);
	vertex[7].position = D3DXVECTOR3(1, -1, 1);

	vertex[0].color = D3DXCOLOR(1, 0, 0, 1);
	vertex[1].color = D3DXCOLOR(0, 1, 0, 1);
	vertex[2].color = D3DXCOLOR(0, 0, 1, 1);
	vertex[3].color = D3DXCOLOR(1, 1, 0, 1);
	vertex[4].color = D3DXCOLOR(1, 0, 1, 1);
	vertex[5].color = D3DXCOLOR(0, 1, 1, 1);
	vertex[6].color = D3DXCOLOR(1, 0, 1, 1);
	vertex[7].color = D3DXCOLOR(0, 1, 1, 1);

	//D3DXCOLOR color = D3DXCOLOR(1, 0, 1, 1);
	//for (int index = 0; index < 8; index++)
	//{
	//	/*color.r -= 0.1f;
	//	color.g -= 0.1f;
	//	color.b -= 0.1f;*/

	//	vertex[index].color = color;
	//}

	D3D11_BUFFER_DESC desc = { 0 };
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(Vertex) * vertexCount;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA  data = { 0 };
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

	index[0] = 0;
	index[1] = 1;
	index[2] = 2;
	index[3] = 2;
	index[4] = 1;
	index[5] = 3;

	index[6] = 1;
	index[7] = 5;
	index[8] = 3;
	index[9] = 3;
	index[10] = 5;
	index[11] = 7;

	index[12] = 5;
	index[13] = 4;
	index[14] = 6;
	index[15] = 5;
	index[16] = 6;
	index[17] = 7;

	index[18] = 4;
	index[19] = 0;
	index[20] = 6;
	index[21] = 0;
	index[22] = 2;
	index[23] = 6;

	index[24] = 0;
	index[25] = 4;
	index[26] = 5;
	index[27] = 0;
	index[28] = 5;
	index[29] = 1;

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

	hr = DEVICE->CreateBuffer(&desc, &data, &indexBuffer);
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
	(
		&rasterizerBuffer,
		&wireFrameRender
	);
	assert(SUCCEEDED(hr));

}

void Cube::Update(float timeDelta)
{
	
}

void Cube::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	DEVICECONTEXT->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DEVICECONTEXT->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	DEVICECONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DEVICECONTEXT->RSSetState(wireFrameRender);
	world = transform->GetFinalMatrix();
	view = CAMERA->GetViewMatrix();
	projection = CAMERA->GetProjectionMatrix();

	shader->SetParameters(world, view, projection);

	shader->Render();

	DEVICECONTEXT->DrawIndexed(indexCount, 0, 0);
}
