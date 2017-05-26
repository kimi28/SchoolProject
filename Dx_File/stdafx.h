#pragma once
//미리 컴파일 해더: 자주 쓰는 파일은 변경하지 않는다.
#include <Windows.h>
#include <assert.h>
#include <stdio.h>

#include <d3d9.h>
#include <d3dx9.h>


#pragma comment(lib, "d3d9.lib")//시스템 라이브러리 거나 프로젝트 내부 라이브러리 불러 올때.
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "winmm.lib")

#pragma warning(disable: 4996)


#define SAFE_RELEASE(p){if ((p)){(p)->Release(); (p) = NULL;}}
#define SAFE_DELETE(a) if((a)!= NULL) delete(a); (a) = NULL;
#define SAFE_DELETE_ARRAY(a) if((a)!=NULL) delete [] (a); (a)=NULL;