#pragma once
class ColorShader
{
private:
	struct MatrixBuffer
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11InputLayout* layout;
	ID3D11Buffer* matrixBuffer;

public:
	ColorShader();
	~ColorShader();

	ID3D11VertexShader* GetVertexShader()
	{
		return vertexShader;
	}
	ID3D11PixelShader* GetPixelShader()
	{
		return pixelShader;
	}

	void SetParameters(D3DXMATRIX world,
		D3DXMATRIX view, D3DXMATRIX projection);

	void Render();
};

