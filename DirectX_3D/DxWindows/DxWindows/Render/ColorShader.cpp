#include "../stdafx.h"
#include "ColorShader.h"



ColorShader::ColorShader()
{
	HRESULT hr;

	ID3D10Blob* errorMessage;

	ID3D10Blob* vertexShaderBuffer;

	hr = D3DX10CompileFromFile
	(
		L"./Shader/ColorVertex.hlsl",
		NULL,
		NULL,
		"ColorVertexShader",
		"vs_5_0",
		D3D10_SHADER_ENABLE_STRICTNESS,
		0,
		NULL,
		&vertexShaderBuffer,
		&errorMessage,
		NULL
	);

	if (FAILED(hr))
	{
		if (errorMessage != NULL)
		{
			string str = (const char*)errorMessage->GetBufferPointer();
			MessageBoxA(NULL, str.c_str(), "Vertex Shader Error", MB_OK);
		}
		assert(false);
	}
	
	hr = DEVICE->CreateVertexShader
	(
		vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(),
		NULL,
		&vertexShader
	);
	assert(SUCCEEDED(hr));

	ID3D10Blob* pixelShaderBuffer;
	hr = D3DX10CompileFromFile
	(
		L"./Shader/ColorPixel.hlsl",
		NULL,
		NULL,
		"ColorPixelShader",
		"ps_5_0",
		D3D10_SHADER_ENABLE_STRICTNESS,
		0,
		NULL,
		&pixelShaderBuffer,
		&errorMessage,
		NULL
	);

	if (FAILED(hr))
	{
		if (errorMessage != NULL)
		{
			string str = (const char*)errorMessage->GetBufferPointer();
			MessageBoxA(NULL, str.c_str(), "Pixel Shader Error", MB_OK);
		}
		assert(false);
	}

	hr = DEVICE->CreatePixelShader
	(
		pixelShaderBuffer->GetBufferPointer(),
		pixelShaderBuffer->GetBufferSize(),
		NULL,
		&pixelShader
	);

	D3D11_INPUT_ELEMENT_DESC layoutDesc[2];
	layoutDesc[0].SemanticName = "POSITION";
	layoutDesc[0].SemanticIndex = 0;
	layoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	layoutDesc[0].InputSlot = 0;
	layoutDesc[0].AlignedByteOffset = 0;
	layoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	layoutDesc[0].InstanceDataStepRate = 0;

	layoutDesc[1].SemanticName = "COLOR";
	layoutDesc[1].SemanticIndex = 0;
	layoutDesc[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	layoutDesc[1].InputSlot = 0;
	layoutDesc[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	layoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	layoutDesc[1].InstanceDataStepRate = 0;

	UINT elements;
	elements = sizeof(layoutDesc) / sizeof(layoutDesc[0]);

	hr = DEVICE->CreateInputLayout
	(
		layoutDesc,
		elements,
		vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(),
		&layout
	);
	assert(SUCCEEDED(hr));

	SAFE_RELEASE(vertexShaderBuffer);
	SAFE_RELEASE(pixelShaderBuffer);

	D3D11_BUFFER_DESC matrixBufferDesc;
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBuffer);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	hr = DEVICE->CreateBuffer
	(
		&matrixBufferDesc,
		NULL,
		&matrixBuffer
	);
	assert(SUCCEEDED(hr));
}


ColorShader::~ColorShader()
{
	SAFE_RELEASE(matrixBuffer);
	SAFE_RELEASE(layout);
	SAFE_RELEASE(pixelShader);
	SAFE_RELEASE(vertexShader);
}

void ColorShader::SetParameters(D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX projection)
{
	HRESULT hr;
	D3DXMatrixTranspose(&world, &world);
	D3DXMatrixTranspose(&view, &view);
	D3DXMatrixTranspose(&projection, &projection);

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	hr = DEVICECONTEXT->Map
	(
		matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource
	);
	assert(SUCCEEDED(hr));

	MatrixBuffer* buffer = (MatrixBuffer*)mappedResource.pData;
	buffer->world = world;
	buffer->view = view;
	buffer->projection = projection;
	DEVICECONTEXT->Unmap(matrixBuffer, 0);
	DEVICECONTEXT->VSSetConstantBuffers(0, 1, &matrixBuffer);
}

void ColorShader::Render()
{
	DEVICECONTEXT->IASetInputLayout(layout);
	DEVICECONTEXT->VSSetShader(vertexShader, NULL, 0);
	DEVICECONTEXT->PSSetShader(pixelShader, NULL, 0);
}