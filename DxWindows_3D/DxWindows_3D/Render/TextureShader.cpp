#include "../stdafx.h"
#include "TextureShader.h"


TextureShader::TextureShader()
{
	HRESULT hr;

	ID3D10Blob* errorMessage;

	ID3D10Blob* vertexShaderBuffer;

	hr = D3DX10CompileFromFile
	(
		L"./Shader/TextureVertex.hlsl",
		NULL,
		NULL,
		"TextureVertexShader",
		"vs_5_0",		//셰이더의 버전 
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
			string str =
				(const char*)errorMessage->GetBufferPointer();
			MessageBoxA(NULL, str.c_str(),
				"Vertex Shader Error", MB_OK);
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
		L"./Shader/TexturePixel.hlsl",
		NULL,
		NULL,
		"TexturePixelShader",
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
	layoutDesc[0].InputSlot = 0; //식별번호
	layoutDesc[0].AlignedByteOffset = 0;
	layoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	layoutDesc[0].InstanceDataStepRate = 0;

	layoutDesc[1].SemanticName = "TEXCOORD";
	layoutDesc[1].SemanticIndex = 0;
	layoutDesc[1].Format = DXGI_FORMAT_R32G32_FLOAT;
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

	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = DEVICE->CreateSamplerState
	(
		&samplerDesc, &samplerState
	);

	assert(SUCCEEDED(hr));
	
}


TextureShader::~TextureShader()
{
	SAFE_RELEASE(matrixBuffer);
	SAFE_RELEASE(layout);
	SAFE_RELEASE(pixelShader);
	SAFE_RELEASE(vertexShader);
	SAFE_RELEASE(samplerState);
}

void TextureShader::SetParameters(D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX projection)
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

	DEVICECONTEXT->PSSetSamplers(0, 1, &samplerState);
}

void TextureShader::Render()
{
	DEVICECONTEXT->IASetInputLayout(layout);
	DEVICECONTEXT->VSSetShader(vertexShader, NULL, 0);
	DEVICECONTEXT->PSSetShader(pixelShader, NULL, 0);
}
