#include "DrawImage.h"
#include <conio.h>
#include <Windows.h>

using namespace Gdiplus;

DrawImage::DrawImage()
{
	GdiplusStartupInput gdiplusStartupInput;
	gdiplusToken = NULL;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput);

	system("mode con:cols=100 lines=50");

	hwnd = GetConsoleWindow();
	hdc = GetDC(hwnd);
	GetClientRect(hwnd, &clientArea);

	foreground = new Gdiplus::Graphics(hdc);
	bitmap = new Gdiplus::Bitmap(clientArea.right, clientArea.bottom);
	background = new Gdiplus::Graphics(bitmap);
}


DrawImage::~DrawImage()
{

}

void DrawImage::Clear(BYTE r, BYTE g, BYTE b)
{
}

void DrawImage::AddImage(WCHAR * fileName)
{
}

void DrawImage::Drawing(int number)
{
}

void DrawImage::Draw(Gdiplus::Image * image, Gdiplus::Rect rect)
{
}

void DrawImage::FlipBuffer()
{
}
