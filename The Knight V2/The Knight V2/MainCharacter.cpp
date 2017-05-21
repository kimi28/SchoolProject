#include "MainCharacter.h"
#include "Character.h"
#include "Vector2D.h"
#include "SceneManager.h"

MainCharacter::MainCharacter(SceneManager* sceneManager) : Character(sceneManager), speed(0, 0)
{
	AddImage(L"resource\\Front_0.png");//0
	AddImage(L"resource\\Front_1.png"); //1
	AddImage(L"resource\\Front_2.png");//2
	AddImage(L"resource\\Front_3.png");//3

	AddImage(L"resource\\Rear_0.png");//4
	AddImage(L"resource\\Rear_1.png");//5
	AddImage(L"resource\\Rear_2.png");//6
	AddImage(L"resource\\Rear_3.png");//7

	AddImage(L"resource\\Right_0.png");//8
	AddImage(L"resource\\Right_1.png");//9
	AddImage(L"resource\\Right_2.png");//10
	AddImage(L"resource\\Right_3.png");//11

	AddImage(L"resource\\Left_0.png");//12
	AddImage(L"resource\\Left_1.png");//13 
	AddImage(L"resource\\Left_2.png");// 14 
	AddImage(L"resource\\Left_3.png");// 15
	this->currentImageIndex = 2;
	this->image = imageList[currentImageIndex];
}

void MainCharacter::AddImage(WCHAR * path)
{
	Image* image = new Gdiplus::Image(path);
	this->rect = { 0, 0, 0, 0 };

	this->rect.Width = image->GetWidth();
	this->rect.Height = image->GetHeight();

	imageList.push_back(image);
}

MainCharacter::MainCharacter(SceneManager* sceneManager, char* name, int hp, int attack, int defence, int critical, int luck)
	: Character(sceneManager, name, hp, attack, defence, critical, luck), speed(0, 0)
	//Character 클래스에서 상속 받으면서 Character 생성자 초기화 및 Vector2D speed 생성자 초기화 하는 방법.
{

}

bool MainCharacter::isCollision(Vector2D direction, RECT rect)
{
	if (direction.X > rect.left
		&& direction.Y > rect.top
		&& direction.X < (rect.right - MainCharacter::GetRect().Width)
		&& direction.Y < (rect.bottom - MainCharacter::GetRect().Height)) {
		return true;
	}
	else {
		Stop();
	}
	return false;
}

void MainCharacter::Move(Vector2D direction)
{
	currentWalkDistance = 0;
	int speed = 150;
	this->speed.X = direction.X * speed;
	this->speed.Y = direction.Y * speed;
}

void MainCharacter::Update(int deltaTime) {

	if (speed.X == 0 && speed.Y == 0)
		return;

	Vector2D direction = this->speed.Normalize();
	bool isCollision = sceneManager->CheckCollision(this, direction);
	if (isCollision)
		return;

	int deltaX = speed.X * deltaTime / 1000;
	int deltaY = speed.Y * deltaTime / 1000;

	if (deltaX > 0) {
		// move right
		if (currentImageIndex < 8 || currentImageIndex > 11) {
			currentImageIndex = 8;
		}
		else {
			currentImageIndex++;
			if (currentImageIndex > 11)
				currentImageIndex = 8;
		}
	}
	else if (deltaX < 0) {
		// move left
		if (currentImageIndex < 12 || currentImageIndex > 15) {
			currentImageIndex = 12;
		}
		else {
			currentImageIndex++;
			if (currentImageIndex > 15)
				currentImageIndex = 12;
		}
	}
	else if (deltaY > 0) {
		// move up
		if (currentImageIndex < 0 || currentImageIndex > 3) {
			currentImageIndex = 0;
		}
		else {
			currentImageIndex++;
			if (currentImageIndex > 3)
				currentImageIndex = 0;
		}
	}
	else if (deltaY < 0) {
		// move down
		if (currentImageIndex < 4 || currentImageIndex > 7) {
			currentImageIndex = 4;
		}
		else {
			currentImageIndex++;
			if (currentImageIndex > 7)
				currentImageIndex = 4;
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