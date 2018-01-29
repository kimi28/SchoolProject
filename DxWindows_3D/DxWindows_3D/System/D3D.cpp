#include "../stdafx.h"
#include "D3D.h"



void D3D::CreateAdapter()
{
	HRESULT hr;
	IDXGIFactory* factory;
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	assert(SUCCEEDED(hr));

	IDXGIAdapter* adapter;
	hr = factory->EnumAdapters(0, &adapter);
	assert(SUCCEEDED(hr));

	IDXGIOutput* adapterOutput;
	hr = adapter->EnumOutputs(0, &adapterOutput);
	assert(SUCCEEDED(hr));

	//디스플레이 (모니터) 정보 출력을 위해서
	UINT modeCount;
	hr = adapterOutput->GetDisplayModeList
	(
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_ENUM_MODES_INTERLACED,
		&modeCount,
		NULL
	);
	DXGI_MODE_DESC* displayModeList = new DXGI_MODE_DESC[modeCount];
	hr = adapterOutput->GetDisplayModeList
	(
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_ENUM_MODES_INTERLACED,
		&modeCount,
		displayModeList
	);
	assert(SUCCEEDED(hr));

	for (int i = 0; i < modeCount; i++)
	{
		bool isCheck = true;
		isCheck &= displayModeList[i].Width == WINSIZE_X;
		isCheck &= displayModeList[i].Height == WINSIZE_Y;

		if (isCheck == true)
		{
			numerator = displayModeList[i].RefreshRate.Numerator;
			denominator = displayModeList[i].RefreshRate.Denominator;
		}
	}

	DXGI_ADAPTER_DESC adapterDesc;
	hr = adapter->GetDesc(&adapterDesc);
	assert(SUCCEEDED(hr));

	gpuMemorySize = adapterDesc.DedicatedVideoMemory / 1024 / 1024;
	gpuDescription = adapterDesc.Description;

	delete[] displayModeList;
	SAFE_RELEASE(adapterOutput);
	SAFE_RELEASE(adapter);
	SAFE_RELEASE(factory);
}

void D3D::CreateSwapChain()
{
	HRESULT hr;
	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = WINSIZE_X;
	swapChainDesc.BufferDesc.Height = WINSIZE_Y;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	//(UNSPECIFIED) 특정 옵션이 지정되지 않았다.
	//
	swapChainDesc.BufferDesc.ScanlineOrdering =
		DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling =
		DXGI_MODE_SCALING_UNSPECIFIED;

	if (isVsync) //수직동기화
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}
	//후면버퍼에 랜더링을 하자
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = g_hWnd;
	//count 1 -> Quality;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = true;
	swapChainDesc.SwapEffect =
		DXGI_SWAP_EFFECT_DISCARD; //장면 전환 될때 마다 이전 내용을 모두 삭제
	swapChainDesc.Flags = 0;  //기타 옵션 

	hr = D3D11CreateDeviceAndSwapChain
	(
		NULL, //장치 설정
		D3D_DRIVER_TYPE_HARDWARE, //디바이스 타입
		NULL,
		0,
		&version,
		1,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&swapChain,
		&device,
		NULL,
		&deviceContext
	);
	assert(SUCCEEDED(hr));
	//백버퍼 포인터

	ID3D11Texture2D* backBufferPointer;
	hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&backBufferPointer);
	assert(SUCCEEDED(hr));

	//백버퍼 포인터를 이용하여 랜더 타겟 뷰 생성
	hr = device->CreateRenderTargetView(
		backBufferPointer, NULL, &renderTargetView);
	assert(SUCCEEDED(hr));

	SAFE_RELEASE(backBufferPointer);

}

void D3D::CreateDepthStencilBuffer()
{
	HRESULT hr;

	//깊이 버퍼 구조체 초기화
	D3D11_TEXTURE2D_DESC depthBufferDesc = { 0 };
	depthBufferDesc.Width = WINSIZE_X;
	depthBufferDesc.Height = WINSIZE_Y;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	hr = device->CreateTexture2D(&depthBufferDesc, NULL, &depthStencilBuffer);
	assert(SUCCEEDED(hr));

	//스탠실 상태 초기화 
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = { 0 };
	depthStencilDesc.DepthEnable = true;									//깊이버퍼 활성화 여부
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;			//깊이버퍼 쓰기 활성화
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;						//깊이 테이터 와 기존 데이터 비교(원본 데이터가 대상 데이터보다 작으면 통과) 

	depthStencilDesc.StencilEnable = true;									//표면 버퍼 여부
	depthStencilDesc.StencilReadMask = 0xFF;								//읽는데 필요한 일부 식별
	depthStencilDesc.StencilWriteMask = 0xFF;								//쓰는데 필요한 일부 식별
																			//표면 법선이 카메라를 향하고 있을때 각버퍼의 테스트 결과 
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;		//표면 버퍼 실패시	 (기존 스탠실 유지)
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;	//표면 버퍼 성공 , 깊이 버퍼 실패시 (표면 값 1증가)
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;		//모두 통과
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;		//현 표면버퍼를 기존 버퍼와 비교 (항상 비교)
																			//표면 법선이 카메라와멀어 을때
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	hr = device->CreateDepthStencilState(&depthStencilDesc, &depthStencilState);
	assert(SUCCEEDED(hr));

	deviceContext->OMSetDepthStencilState(depthStencilState, 1);

	//스탠실 뷰 초기화
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;				//(깊이 24, 표면 8, 지원 32비트 z버퍼 형식)
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;			//리소스 텍스쳐는 2D로
	depthStencilViewDesc.Texture2D.MipSlice = 0;								//텍스처 깊이 표면

																				//깊이 표면 생성 
	hr = device->CreateDepthStencilView(depthStencilBuffer, &depthStencilViewDesc, &depthStencilView);
	assert(SUCCEEDED(hr));

	deviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	//레스터 라이즈 초기화 
	D3D11_RASTERIZER_DESC rasterDesc;
	ZeroMemory(&rasterDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	hr = device->CreateRasterizerState(&rasterDesc, &rasterizerState);
	assert(SUCCEEDED(hr));

	deviceContext->RSSetState(rasterizerState);

	//스텐실 사용 안함 
	D3D11_DEPTH_STENCIL_DESC depthDisabledStencilDesc = { 0 };
	depthDisabledStencilDesc.DepthEnable = false;
	depthDisabledStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthDisabledStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthDisabledStencilDesc.StencilEnable = true;
	depthDisabledStencilDesc.StencilReadMask = 0xFF;
	depthDisabledStencilDesc.StencilWriteMask = 0xFF;
	depthDisabledStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthDisabledStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthDisabledStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthDisabledStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	hr = device->CreateDepthStencilState(&depthDisabledStencilDesc, &depthStencilDisableState);
	assert(SUCCEEDED(hr));
}

D3D::D3D()
{
	version = D3D_FEATURE_LEVEL_11_0;
	isVsync = false;

	numerator = 0;
	denominator = 1;

	CreateAdapter();
	CreateSwapChain();
	CreateDepthStencilBuffer();
}


D3D::~D3D()
{
	if (swapChain != NULL)
		swapChain->SetFullscreenState(false, NULL);

	SAFE_RELEASE(rasterizerState);
	SAFE_RELEASE(depthStencilView);
	SAFE_RELEASE(depthStencilState);
	SAFE_RELEASE(depthStencilBuffer);
	SAFE_RELEASE(renderTargetView);
	SAFE_RELEASE(deviceContext);
	SAFE_RELEASE(device);
	SAFE_RELEASE(swapChain);
}

void D3D::BeginScene(float r, float g, float b, float a)
{
	//0~255 , 0 ~ 1.0f
	D3DXCOLOR color = { r,g,b,a };
	//화면의 내용을 지운다.
	deviceContext->ClearRenderTargetView
	(
		renderTargetView,
		color
	);
	deviceContext->ClearDepthStencilView
	(
		depthStencilView,   //지우는 대상
		D3D11_CLEAR_DEPTH, //옵션
		1,				   //(depth)다시 초기화 해주는 값
		0					//Stencil
	);
}

void D3D::EndScene()
{
	//후면버퍼에 작성한 내용을 전면버퍼에 넘겨준다.
	if (isVsync == true)
		swapChain->Present(1, 0);
	else
		swapChain->Present(0, 0);

}
