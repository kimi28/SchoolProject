#include "DrawImage.h"

struct ImageInfo {
	WCHAR* path;
	Gdiplus::Image* image;
};

enum MoveDirection {
	Left,
	Right,
	Up,
	Down,
};
#pragma once
class MainCharacter
{
protected:
	DrawImage* drawImage;
	ImageInfo* images;
	Gdiplus::Rect position;
	int drawIndex;
	int imageAddIndex;
	MoveDirection direction;
public:
	MainCharacter(DrawImage* drawImage);
	~MainCharacter();

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void Redraw();

private:
	void AddImage(WCHAR* path) {
		ImageInfo imageInfo;
		imageInfo.path = path;

		Gdiplus::Image* gdiImage = new Gdiplus::Image(path);
		imageInfo.image = gdiImage;

		images[imageAddIndex] = imageInfo;
		imageAddIndex++;
	}
};

