#pragma once
#include "../Manager/SingletonBase.h"

class TweakBar : public SingletonBase<TweakBar>
{
private:
	bool isDraw;
	TwBar* bar;
public:
	TweakBar();
	~TweakBar();

	void Init();
	void InputProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void Render();

	void GetDraw(bool* isDraw)
	{
		*isDraw = this->isDraw;
	}
	void SetDraw(bool isDraw)
	{
		this->isDraw = isDraw;

		if (isDraw == true)
			TwDefine("TweakBar visible=true");
		else
			TwDefine("TweakBar visible=false");
	}
	void ChangeDraw()
	{
		SetDraw(!isDraw);
	}
	TwBar* GetBar()
	{
		return bar;
	}
};

#define TWEAKBAR TweakBar::GetInstance()