#include "MainCharacter.h"



void MainCharacter::AddImage(WCHAR * path)
{
	Image* image = new Gdiplus::Image(path);
	this->rect = { 0, 0, 0, 0 };

	this->rect.Width = image->GetWidth();
	this->rect.Height = image->GetHeight();

	imageList.push_back(image);
}

MainCharacter::MainCharacter() : speed(0, 0)
{

	AddImage(L"resource\\Front_1.png"); //0
	AddImage(L"resource\\Front_2.png");//1
	AddImage(L"resource\\Front_3.png");//2

	AddImage(L"resource\\Rear_1.png");//3
	AddImage(L"resource\\Rear_2.png");//4
	AddImage(L"resource\\Rear_3.png");//5

	AddImage(L"resource\\Right_1.png");//6
	AddImage(L"resource\\Right_2.png");//7
	AddImage(L"resource\\Right_3.png");//8

	AddImage(L"resource\\Left_1.png");// 9 
	AddImage(L"resource\\Left_2.png");// 10 
	AddImage(L"resource\\Left_3.png");// 11
	this->currentImageIndex = 1;
	this->image = imageList[currentImageIndex];
}

void MainCharacter::Move(Vector2D direction)
{
	currentWalkDistance = 0;
	int speed = 100;
	this->speed.X = direction.X * speed;
	this->speed.Y = direction.Y * speed;
}

void MainCharacter::Update(int deltaTime) {

	if (speed.X == 0 && speed.Y == 0)
		return;

	int deltaX = speed.X * deltaTime / 1000;
	int deltaY = speed.Y * deltaTime / 1000;

	if (deltaX > 0) {
		// move right
		if (currentImageIndex < 6 || currentImageIndex > 8) {
			currentImageIndex = 6;
		}
		else {
			currentImageIndex++;
			if (currentImageIndex > 8)
				currentImageIndex = 6;
		}
	}
	else if (deltaX < 0) {
		// move left
		if (currentImageIndex < 9 || currentImageIndex > 11) {
			currentImageIndex = 9;
		}
		else {
			currentImageIndex++;
			if (currentImageIndex > 11)
				currentImageIndex = 9;
		}
	}
	else if (deltaY > 0) {
		// move up
		if (currentImageIndex < 0 || currentImageIndex > 2) {
			currentImageIndex = 0;
		}
		else {
			currentImageIndex++;
			if (currentImageIndex > 2)
				currentImageIndex = 0;
		}
	}
	else if (deltaY < 0) {
		// move down
		if (currentImageIndex < 3 || currentImageIndex > 5) {
			currentImageIndex = 3;
		}
		else {
			currentImageIndex++;
			if (currentImageIndex > 5)
				currentImageIndex = 3;
		}
	}

	this->image = imageList[currentImageIndex];

	this->SetPosition(this->position.X + deltaX, this->position.Y + deltaY);

	currentWalkDistance += pow(pow(deltaX, 2) + pow(deltaY, 2), 0.5);
	if (currentWalkDistance >= 50) {
		Stop();
		currentWalkDistance = 0;
	}
}

void MainCharacter::Stop()
{
	speed.X = 0;
	speed.Y = 0;
}

MainCharacter::~MainCharacter()
{
}


