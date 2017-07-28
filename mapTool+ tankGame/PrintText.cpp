#include "stdafx.h"
#include "PrintText.h"

PrintText* PrintText::instance = NULL;

PrintText * PrintText::GetInstance()
{
	if (instance == NULL)
		instance = new PrintText();

	return instance;
}

void PrintText::DeleteInstance()
{
	SAFE_DELETE(instance);
}

void PrintText::SetDevice(LPDIRECT3DDEVICE9 device)
{
	this->device = device;
	rect = { 5, 5, 0, 0 };
	HRESULT hr = D3DXCreateFont(device, 
		12, 0, 0, 1, 
		false, 
		DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, 
		DEFAULT_QUALITY, 
		DEFAULT_PITCH | FF_DONTCARE, 
		L"µ¸¿ò", 
		&font);
	assert(hr == S_OK);

	hr = D3DXCreateSprite(device, &sprite);
	assert(hr == S_OK);
}

void PrintText::AddText(wstring value)
{
	data += value + L"\n";
}

void PrintText::Render()
{
  	if (data.size() > 0)
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);

		
		font->DrawTextW(
			sprite, 
			data.c_str(), 
			-1, 
			&rect, 
			DT_NOCLIP, 
			D3DCOLOR(0xFF0000FF)
		);

		sprite->End();

		data = L"";
	}
}
void PrintText::SetCoord(POINT coord)
{
	rect = { coord.x ,coord.y, 0, 0 };
}

PrintText::PrintText()
{
}


PrintText::~PrintText()
{
	SAFE_RELEASE(font);
	SAFE_RELEASE(sprite);
}
