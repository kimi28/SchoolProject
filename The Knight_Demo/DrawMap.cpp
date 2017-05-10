#include "DrawMap.h"
#include <conio.h>
#include <Windows.h>

using namespace Gdiplus;

DrawMap::DrawMap()
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


DrawMap::~DrawMap()
{
	ReleaseDC(hwnd, hdc);

	for (int i = 0; i < (int)imagePositions.size(); i++) {
		delete imagePositions[i].mapImage;
	}

	delete bitmap;
	delete background;
	delete foreground;
	Gdiplus::GdiplusShutdown(gdiplusToken);
}

void DrawMap::Clear(BYTE r, BYTE g, BYTE b)
{
	Color color = { r, g, b };
	background->Clear(color);
}

void DrawMap::AddMap(WCHAR * fileName)
{
	Gdiplus::Image* mapImage = new Gdiplus::Image(fileName);

	MapPosition position;
	position.mapImage = mapImage;
	position.rect = { 0, 0, 0, 0 };

	position.rect.Width = mapImage->GetWidth();
	position.rect.Height = mapImage->GetHeight();

	imagePositions.push_back(position);
}

void DrawMap::Drawing(int number)
{
	MapPosition position = imagePositions[number];
	background->DrawImage(position.mapImage, position.rect);
}

void DrawMap::Drawing(int number, Gdiplus::Rect rect)
{
	MapPosition position = imagePositions[number];
	position.rect = rect;
	background->DrawImage(position.mapImage, position.rect);
}

void DrawMap::FlipBuffer()
{
	foreground->DrawImage(bitmap, 0, 0);
}