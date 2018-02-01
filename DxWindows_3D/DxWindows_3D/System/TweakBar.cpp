#include "../stdafx.h"
#include "TweakBar.h"



TweakBar::TweakBar()
{
}


TweakBar::~TweakBar()
{
	TwTerminate();
}

void TweakBar::Init()
{
	isDraw = false;

	BOOL result = TwInit(TW_DIRECT3D11, DEVICE);
	assert(result == TRUE);
	bar = TwNewBar("TweakBar");
	TwDefine("TweakBar color='0 128 255' alpha=128");
	TwDefine("TweakBar size='250 700'");
	TwDefine("TweakBar valueswidth=120");
	TwDefine("TweakBar visible=false");

}

void TweakBar::InputProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	TwEventWin(hwnd, msg, wParam, lParam);
}

void TweakBar::Render()
{
	TwDraw();
}
