#pragma once
class Transform;
class ColorShader;
class Cube
{
private:
	D3DXMATRIX world, view, projection;

	Transform * transform;
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

	D3DXVECTOR3 angle;
	D3DXVECTOR3 position;

	ID3D11RasterizerState* wireFrameRender;
public:
	Cube(ColorShader* shader);
	~Cube();

	void CreateVertexBuffer();
	void CreateIndexBuffer();
	void CreateRenderState();

	void Update(float timeDelta);
	void Render();

	Transform* GetTransform() { return transform; }

};

