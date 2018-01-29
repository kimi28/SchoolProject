#pragma once
class ColorShader;
class Star
{
private:
	D3DXMATRIX world, view, projection;
	D3D11_VIEWPORT viewport;

	ColorShader* shader;

	struct Vertex
	{
		D3DXVECTOR3 position;
		D3DXCOLOR color;
	};

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* IndexBuffer;

	UINT vertexCount;
	UINT indexCount;

	float angle;
public:
	Star(ColorShader* shader);
	~Star();

	void CreateVertexBuffer();
	void CreateIndexBuffer();
	void Update(float timeDelta);
	void Render();
};

