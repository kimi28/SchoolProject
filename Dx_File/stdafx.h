#pragma once
//�̸� ������ �ش�: ���� ���� ������ �������� �ʴ´�.
#include <Windows.h>
#include <assert.h>
#include <stdio.h>

#include <d3d9.h>
#include <d3dx9.h>


#pragma comment(lib, "d3d9.lib")//�ý��� ���̺귯�� �ų� ������Ʈ ���� ���̺귯�� �ҷ� �ö�.
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "winmm.lib")

#pragma warning(disable: 4996)


#define SAFE_RELEASE(p){if ((p)){(p)->Release(); (p) = NULL;}}
#define SAFE_DELETE(a) if((a)!= NULL) delete(a); (a) = NULL;
#define SAFE_DELETE_ARRAY(a) if((a)!=NULL) delete [] (a); (a)=NULL;