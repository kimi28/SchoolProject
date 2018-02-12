#pragma once


#include <Windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <assert.h>
#include <time.h>
#pragma comment(lib, "winmm.lib")

#include <vector>
#include <map>
#include <string>

using namespace std;

#include <DXGI.h>
#include <D3Dcommon.h>
#include <d3d11.h>
#include <D3DX10math.h>
#include <D3DX11async.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#include "./Manager/SingletonBase.h"

#include "./System/D3D.h"

#define	WINSIZE_X	800
#define	WINSIZE_Y	800
#define	WINPOS_X	0
#define	WINPOS_Y	0
#define	WIN_CLASS	L"DxWindow"
#define	WIN_TITLE	L"DxWindow"
#define	WIN_STYLE	WS_OVERLAPPEDWINDOW

#define	ONE_RAD	0.017453f

#define SAFE_DELETE(p) if(p) {delete(p); (p) = NULL;}
#define SAFE_RELEASE(p) if(p) {(p)->Release(); (p) = NULL;}
#define SAFE_DELETE_ARRAY(p) if(p) {delete[](p); (p) = NULL;}

extern	HWND	g_hWnd;
extern	HINSTANCE	g_hInst;