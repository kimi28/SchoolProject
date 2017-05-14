#include "SceneManager.h"
#include "Vector2D.h"
#include <thread>

SceneManager::SceneManager()
{
	this->drawImage = new DrawImage();
	thread thread(&Update);
}

SceneManager::~SceneManager()
{
	delete drawImage;
}

void SceneManager::Update()
{
	while (true) {
		Sleep(10);

		// 各种运算
		// 重绘
		
	}
}

bool SceneManager::isCollision(Vector2D direction) // 1->up, 2-> down, 3->left, 4->right
{
	Gdiplus::Rect rectNpc;
	rectNpc = drawImage->GetPosition(1);

	int deltaX = rect.X - rectNpc.X;
	int deltaY = rect.Y - rectNpc.Y;
	if (abs(deltaX) <= rectNpc.Width &&
		abs(deltaY) <= rectNpc.Height) {
		Vector2D distance(deltaX, deltaY);
		int angle = direction.angle(distance);
		printf("angle -> %d\n", angle);
		if (angle < 90)
			return true;
	}

	return false;

}

void SceneManager::MoveUp(int number)
{
	// direction = Vector2D::Up
	// speed = 100 
	if (isCollision(Vector2D::Up) == false) {
		if (characterY > backgroudY) {
			rect = drawImage->GetPosition(number + 6);
			rect.X = characterX;
			rect.Y = characterY - 20;
			drawImage->SetPosition(number + 6, rect.X, rect.Y);
			characterX = rect.X;
			characterY = rect.Y;
		}
		else {
			rect = drawImage->GetPosition(number + 6);
			drawImage->SetPosition(number + 6, characterX, characterY);
		}
	}
	else {
		rect = drawImage->GetPosition(number + 6);
		drawImage->SetPosition(number + 6, characterX, characterY);
	}

}

void SceneManager::MoveDown(int number)
{
	if (isCollision(Vector2D::Down) == false) {
		if (characterY < (backgroudHeight - rect.Height)) {
			rect = drawImage->GetPosition(number + 3);
			rect.X = characterX;
			rect.Y = characterY + 20;
			drawImage->SetPosition(number + 3, rect.X, rect.Y);
			characterX = rect.X;
			characterY = rect.Y;
		}
		else {
			rect = drawImage->GetPosition(number + 3);
			drawImage->SetPosition(number + 3, characterX, characterY);
		}
	}
	else {
		rect = drawImage->GetPosition(number + 3);
		drawImage->SetPosition(number + 3, characterX, characterY);
	}
}

void SceneManager::MoveRight(int number)
{
	if (isCollision(Vector2D::Right) == false) {
		if (characterX < (backgroudWidth - rect.Width)) {
			rect = drawImage->GetPosition(number + 9);
			rect.X = characterX + 20;
			rect.Y = characterY;
			drawImage->SetPosition(number + 9, rect.X, rect.Y);
			characterX = rect.X;
			characterY = rect.Y;
		}
		else {
			rect = drawImage->GetPosition(number + 9);
			drawImage->SetPosition(number + 9, characterX, characterY);
		}
	}
	else {
		rect = drawImage->GetPosition(number + 9);
		drawImage->SetPosition(number + 9, characterX, characterY);
	}
}

void SceneManager::MoveLeft(int number)
{
	if (isCollision(Vector2D::Left) == false) {
		if (characterX > backgroudX) {
			rect = drawImage->GetPosition(number + 12);
			rect.X = characterX - 20;
			rect.Y = characterY;
			drawImage->SetPosition(number + 12, rect.X, rect.Y);
			characterX = rect.X;
			characterY = rect.Y;
		}
		else {
			rect = drawImage->GetPosition(number + 12);
			drawImage->SetPosition(number + 12, characterX, characterY);

		}
	}
	else {
		rect = drawImage->GetPosition(number + 12);
		drawImage->SetPosition(number + 12, characterX, characterY);
	}
}

void SceneManager::SetPosition()
{
	backgroudWidth = drawImage->GetClientArea().right;
	backgroudHeight = drawImage->GetClientArea().bottom;
	backgroudX = 0;
	backgroudY = 0;
	characterX = backgroudWidth / 2;
	characterY = backgroudHeight / 2;
	npcX = 100;
	npcY = 100;

	drawImage->SetPosition(0, Gdiplus::Rect(backgroudX, backgroudY, backgroudWidth, backgroudHeight));
	drawImage->SetPosition(1, npcX, npcY);

	for (int i = 3; i < (int)drawImage->GetImageCount(); i++)
	{
		drawImage->SetPosition(i, characterX, characterY);
	}
}

void SceneManager::SetPositionDungeon()
{
	backgroudWidth = drawImage->GetClientArea().right;
	backgroudHeight = drawImage->GetClientArea().bottom;
	backgroudX = 0;
	backgroudY = 0;
	characterX = backgroudWidth / 2;
	characterY = backgroudHeight / 2;
	npcX = 100;
	npcY = 100;

	drawImage->SetPosition(2, npcX, npcY);

	for (int i = 3; i < (int)drawImage->GetImageCount(); i++)
	{
		drawImage->SetPosition(i, characterX, characterY);

		if (i == 15) {

			drawImage->SetPosition(15, Gdiplus::Rect(backgroudX, backgroudY, backgroudWidth, backgroudHeight));
		}
	}
}

void SceneManager::AddImage()
{
	drawImage->AddImage(L"resource\\Lobby_Background.png");//0
	drawImage->AddImage(L"resource\\Npc_1.png");//1
	drawImage->AddImage(L"resource\\Npc_2.png");//2

	drawImage->AddImage(L"resource\\Front_1.png");//3
	drawImage->AddImage(L"resource\\Front_2.png");//4
	drawImage->AddImage(L"resource\\Front_3.png");//5

	drawImage->AddImage(L"resource\\Rear_1.png");//6
	drawImage->AddImage(L"resource\\Rear_2.png");//7
	drawImage->AddImage(L"resource\\Rear_3.png");//8

	drawImage->AddImage(L"resource\\Right_1.png");//9
	drawImage->AddImage(L"resource\\Right_2.png");//10
	drawImage->AddImage(L"resource\\Right_3.png");//11

	drawImage->AddImage(L"resource\\Left_1.png");//12
	drawImage->AddImage(L"resource\\Left_2.png");//13
	drawImage->AddImage(L"resource\\Left_3.png");//14

	drawImage->AddImage(L"resource\\Dungeon_Background.png");//15

}

void SceneManager::ReDraw(int number)
{
	drawImage->Clear(0, 0, 0);
	for (int i = 0; i < 2; i++)
	{
		drawImage->Drawing(i);

	}
	drawImage->Drawing(number);

	drawImage->FlipBuffer();
}

void SceneManager::ReDrawDungeon(int number)
{
	drawImage->Clear(0, 0, 0);

	drawImage->Drawing(15);
	drawImage->Drawing(2);
	drawImage->Drawing(number);

	drawImage->FlipBuffer();
}


