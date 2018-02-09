#pragma once
class Transform;
class ColorShader;
class TextureShader;
class Cube
{
private:
	D3DXMATRIX world, view, projection;
	
	Transform* transform;

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

	D3DXVECTOR3 angle;
	D3DXVECTOR3 position;

	ID3D11RasterizerState* wireFrameRender;

	ID3D11ShaderResourceView* texture;

public:
	Cube(TextureShader* shader);
	~Cube();

	void CreateVertexBuffer(
		ST_TEXTURE_RANGE stRagne,
		int widthRatio = 1,
		int heightRatio = 1,
		int depthRatio = 1);
	void CreateIndexBuffer();
	void CreateRenderState();

	void Update(float timeDelta);
	void Render();

	Transform* GetTransform() {
		return transform;
	}
};

