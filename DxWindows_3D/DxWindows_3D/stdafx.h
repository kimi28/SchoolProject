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

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <d3dx10math.h>
#include <D3DX11async.h>

#pragma comment(lib, "dxgi.h")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#include "AntTweakBar.h"
#pragma comment(lib, "AntTweakBar.lib")

#include "./Manager/SingletonBase.h"

#include "./System/D3D.h"
#include "./System/Frame.h"
#include "./System/TweakBar.h"
#include "./System/Input.h"

#define WINSIZE_X 1280
#define WINSIZE_Y 800
#define WINPOS_X 0
#define WINPOS_Y 0
#define WIN_CLASS L"DxWindow"
#define WIN_TITLE L"DxWindow"
#define WIN_STYLE WS_OVERLAPPEDWINDOW

#define ONE_RAD 0.017453f

#define SAFE_DELETE(p) {if(p) {delete(p); (p) = NULL;}}
#define SAFE_RELEASE(p) {if(p) {(p)->Release(); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p) {delete[](p); (p) = NULL;}}

extern HWND g_hWnd;
extern HINSTANCE g_hInst;