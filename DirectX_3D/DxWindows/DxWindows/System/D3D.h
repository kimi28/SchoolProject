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

public:
	D3D();
	~D3D();
};

