#include "SceneManager.h"
#include "DrawImage.h"

SceneManager::SceneManager()
{
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	this->posX = posX;
	this->posY = posY;
	this->Width = Width;
	this->Height = Height;
	this->Npc_posX = Npc_posX;
	this->Npc_posY = Npc_posY;
}

SceneManager::~SceneManager()
{
}

void SceneManager::MoveUp(DrawImage * drawImage, SceneManager * sceneManager, int number)
{
	if (posY > y) {
		rect = drawImage->GetPosition(number + 6);
		rect.X = posX;
		rect.Y = posY - 20;
		drawImage->SetPosition(number + 6, rect.X, rect.Y);
		sceneManager->ReDraw(drawImage, number + 6);
		posX = rect.X;
		posY = rect.Y;
	}
	else {
		rect = drawImage->GetPosition(number + 6);
		drawImage->SetPosition(number + 6, posX, posY);
		sceneManager->ReDraw(drawImage, number + 6);
	}

}

void SceneManager::MoveDown(DrawImage * drawImage, SceneManager * sceneManager, int number)
{

		if (posY < (height - Height)) {
			rect = drawImage->GetPosition(number + 3);
			rect.X = posX;
			rect.Y = posY + 20;
			drawImage->SetPosition(number + 3, rect.X, rect.Y);
			sceneManager->ReDraw(drawImage, number + 3);
			posX = rect.X;
			posY = rect.Y;
		}
		else {
			rect = drawImage->GetPosition(number + 3);
			drawImage->SetPosition(number + 3, posX, posY);
			sceneManager->ReDraw(drawImage, number + 3);
		}
}

void SceneManager::MoveRight(DrawImage * drawImage, SceneManager * sceneManager, int number)
{
		if (posX < (width - Width)) {
			rect = drawImage->GetPosition(number + 9);
			rect.X = posX + 20;
			rect.Y = posY;
			drawImage->SetPosition(number + 9, rect.X, rect.Y);
			sceneManager->ReDraw(drawImage, number + 9);
			posX = rect.X;
			posY = rect.Y;
		}
		else {
			rect = drawImage->GetPosition(number + 9);
			drawImage->SetPosition(number + 9, posX, posY);
			sceneManager->ReDraw(drawImage, number + 9);
		}
}

void SceneManager::MoveLeft(DrawImage * drawImage, SceneManager * sceneManager, int number)
{
		if (posX > x) {
			rect = drawImage->GetPosition(number + 12);
			rect.X = posX - 20;
			rect.Y = posY;
			drawImage->SetPosition(number + 12, rect.X, rect.Y);
			sceneManager->ReDraw(drawImage, number + 12);
			posX = rect.X;
			posY = rect.Y;

		}
		else {
			rect = drawImage->GetPosition(number + 12);
			drawImage->SetPosition(number + 12, posX, posY);
			sceneManager->ReDraw(drawImage, number + 12);
		}
}

void SceneManager::SetPosition(DrawImage* drawImage)
{
	width = drawImage->GetClientArea().right;
	height = drawImage->GetClientArea().bottom;
	x = 0;
	y = 0;
	posX = width / 2;
	posY = height / 2;
	Width = 40;
	Height = 60;
	Npc_posX = 100;
	Npc_posY = 100;

	drawImage->SetPosition(0, Gdiplus::Rect(x, y, width, height));
	drawImage->SetPosition(1, Npc_posX, Npc_posY);
	drawImage->SetPosition(2, 700, 100);

	for (int i = 3; i < (int)drawImage->GetImageCount(); i++)
	{
		drawImage->SetPosition(i, posX, posY);
	}
}

void SceneManager::AddImage(DrawImage* drawImage)
{
	drawImage->AddImage(L"resource\\Background.png");//0
	drawImage->AddImage(L"resource\\Npc.png");//1
	drawImage->AddImage(L"resource\\Npc2.png");//2

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

}

void SceneManager::ReDraw(DrawImage* drawImage, int number)
{
	drawImage->Clear(0, 0, 0);
	for (int i = 0; i < 3; i++)
	{
		drawImage->Drawing(i);

	}
	drawImage->Drawing(number);
	drawImage->FlipBuffer();
}


