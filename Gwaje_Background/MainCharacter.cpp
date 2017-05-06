#include "MainCharacter.h"
#include "DrawImage.h"


MainCharacter::MainCharacter(DrawImage* drawImage)
{
	this->drawImage = drawImage;
	drawIndex = 0;
	position = { 0, 0, 0, 0 };
	images = new ImageInfo[12];
	imageAddIndex = 0;
	direction = Left;

	AddImage(L"resource\\Front_1.png");//0
	AddImage(L"resource\\Front_2.png");//1
	AddImage(L"resource\\Front_3.png");//2
	AddImage(L"resource\\Rear_1.png");//3
	AddImage(L"resource\\Rear_2.png");//4
	AddImage(L"resource\\Rear_3.png");//5
	AddImage(L"resource\\Right_1.png");//6
	AddImage(L"resource\\Right_2.png");//7
	AddImage(L"resource\\Right_3.png");//8
	AddImage(L"resource\\Left_1.png");//9
	AddImage(L"resource\\Left_2.png");//10
	AddImage(L"resource\\Left_3.png");//11
}

MainCharacter::~MainCharacter()
{
}

void MainCharacter::MoveLeft()
{
	position.X -= 20;
	if (direction == Left) {
		drawIndex++;
		if (drawIndex >= 12) {
			drawIndex = 9;
		}
	}
	else {
		drawIndex = 9;
	}

	Redraw();
	direction = Left;

}

void MainCharacter::MoveRight()
{
	position.X += 20;
	if (direction == Right) {
		drawIndex++;
		if (drawIndex >= 9) {
			drawIndex = 6;
		}
	}
	else {
		drawIndex = 6;
	}
	Redraw();
	direction = Right;
}

void MainCharacter::MoveUp()
{
	position.Y -= 20;
	if (direction == Up) {
		drawIndex++;
		if (drawIndex >= 6) {
			drawIndex = 3;
		}
	}
	else {
		drawIndex = 3;
	}
	Redraw();
	direction = Up;
}

void MainCharacter::MoveDown()
{
	position.Y += 20;
	if (direction == Down) {
		drawIndex++;
		if (drawIndex >= 3) {
			drawIndex = 0;
		}
	}
	else {
		drawIndex = 0;
	}
	Redraw();
	direction = Down;
}

void MainCharacter::Redraw()
{
	ImageInfo image = images[drawIndex];
	drawImage->Draw(image.image, position);
	drawImage->FlipBuffer();
}
