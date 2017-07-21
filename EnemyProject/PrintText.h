#pragma once
class PrintText
{
public:
	static PrintText* GetInstance();
	static void DeleteInstance();

	void SetDevice(LPDIRECT3DDEVICE9 device);
	void AddText(wstring value);

	void SetCoord(POINT coord);
	void Render();

private:
	PrintText();
	~PrintText();

	static PrintText * instance;

	LPDIRECT3DDEVICE9 device;

	LPD3DXFONT font;
	LPD3DXSPRITE sprite;

	wstring data;
	RECT rect;
};

