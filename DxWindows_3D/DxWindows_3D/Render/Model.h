#pragma once
class ColorShader;
class Model
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
	Model(ColorShader* shader);
	~Model();

	void CreateVertexBuffer();
	void CreateIndexBuffer();
	void Update(float timeDelta);
	void Render();
};

