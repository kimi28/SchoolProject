#include "DrawImage.h"
#include <conio.h>
#include <Windows.h>

using namespace Gdiplus;

DrawImage::DrawImage()
{
	GdiplusStartupInput gdiplusStartupInput;
	gdiplusToken = NULL;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

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
	ReleaseDC(hwnd, hdc);

	for (int i = 0; i < (int)imagePositions.size(); i++) {
		delete imagePositions[i].image;
	}

	delete bitmap;
	delete background;
	delete foreground;
	Gdiplus::GdiplusShutdown(gdiplusToken);
}

void DrawImage::Clear(BYTE r, BYTE g, BYTE b)
{
	Color color = { r, g, b };
	background->Clear(color);
}

void DrawImage::AddImage(WCHAR * fileName)
{
	Gdiplus::Image* image = new Gdiplus::Image(fileName);

	ImagePosition position;
	position.image = image;
	position.rect = { 0, 0, 0, 0 };

	position.rect.Width = image->GetWidth();
	position.rect.Height = image->GetHeight();

	imagePositions.push_back(position);
}

void DrawImage::Drawing(int number)
{
	ImagePosition position = imagePositions[number];
	background->DrawImage(position.image, position.rect);
}

void DrawImage::Drawing(int number, Gdiplus::Rect rect)
{
	ImagePosition position = imagePositions[number];
	position.rect = rect;
	background->DrawImage(position.image, position.rect);
}

void DrawImage::FlipBuffer()
{
	foreground->DrawImage(bitmap, 0, 0);
}
