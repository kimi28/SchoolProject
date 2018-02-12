#pragma once
class D3D : public SingletonBase<D3D>
{
private:
	void CreateAdapter();
	void CreateSwapChain();
	void CreateDepthStencilBuffer();

	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;

	D3D_FEATURE_LEVEL	version;

	bool isVsync;
	UINT gpuMemorySize;
	wstring gpuDescription;

	UINT numerator;
	UINT denominator;

	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* renderTargetView;
	ID3D11Texture2D* depthStencilBuffer;

	ID3D11DepthStencilState* depthStencilState;
	ID3D11DepthStencilState* depthStencilDisableState;
	ID3D11DepthStencilView* depthStencilView;
	ID3D11RasterizerState* rasterizerState;

public:
	D3D();
	~D3D();

	ID3D11Device* GetDevice()
	{
		return device;
	}

	ID3D11DeviceContext* GetDeviceContext()
	{
		return deviceContext;
	}

	void BeginScene(float r, float g, float b, float a);
	void EndScene();
};

#define	DEVICE	D3D::GetDevice()
#define	DEVICECONTEXT	D3D::GetDeviceContext()

