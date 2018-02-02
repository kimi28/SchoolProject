#pragma once
class ColorShader;
class TextureShader;
class Model
{
private:
	D3DXMATRIX world, view, projection;
	D3D11_VIEWPORT viewport;

	TextureShader* shader;

	struct Vertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 uv;
	};

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* IndexBuffer;

	UINT vertexCount;
	UINT indexCount;

	float angle;

	ID3D11ShaderResourceView* texture;
public:
	Model(TextureShader* shader);
	~Model();

	void CreateVertexBuffer();
	void CreateIndexBuffer();
	void Update(float timeDelta);
	void Render();
};

