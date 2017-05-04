#pragma once
#include <vector>
#include <Windows.h>
#include <gdiplus.h>

using namespace std;

struct ImagePosition {
	Gdiplus::Image* image;
	Gdiplus::Rect rect;
};

class DrawImage
{
private:
	Gdiplus::Graphics* foreground;
	Gdiplus::Graphics* background;
	Gdiplus::Bitmap* bitmap;
	ULONG_PTR gdiplusToken;

	HWND hwnd;
	HDC hdc;

	vector<ImagePosition> imagePositions;
	RECT clientArea;

public:
	DrawImage();
	~DrawImage();

	RECT GetClientArea() {
		return clientArea;
	}

	ImagePosition GetImagePosition(int number) {
		return imagePositions[number];
	}

	Gdiplus::Rect GetPosition(int number) {
		
		return imagePositions[number].rect;
	}

	void SetPosition(int number, Gdiplus::Rect rect) {
		imagePositions[number].rect = rect;
	}

	void SetPosition(int number, int x, int y) {
		Gdiplus::Rect rect = imagePositions[number].rect;
		rect.X = x;
		rect.Y = y;

		imagePositions[number].rect = rect;
	}

	int GetImageCount() {
		return (int)imagePositions.size();
	}

	void Clear(BYTE r, BYTE g, BYTE b);
	void AddImage(WCHAR* fileName);
	void Drawing(int number);
	void Draw(Gdiplus::Image* image, Gdiplus::Rect rect);
	void FlipBuffer();
};

