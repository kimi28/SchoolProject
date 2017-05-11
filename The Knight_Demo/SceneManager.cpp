#include "SceneManager.h"
#include "DrawImage.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::MoveUp(DrawImage * drawImage, SceneManager * sceneManager, int number)
{
	if (characterY > mapY) {
		rect = drawImage->GetPosition(number + 6);
		rect.X = characterX;
		rect.Y = characterY - 20;
		drawImage->SetPosition(number + 6, rect.X, rect.Y);
		sceneManager->ReDraw(drawImage, number + 6);
		characterX = rect.X;
		characterY = rect.Y;
	}
	else {
		rect = drawImage->GetPosition(number + 6);
		drawImage->SetPosition(number + 6, characterX, characterY);
		sceneManager->ReDraw(drawImage, number + 6);
	}

}

void SceneManager::MoveDown(DrawImage * drawImage, SceneManager * sceneManager, int number)
{

	if (characterY < (mapHeight - HEIGHT)) {
		rect = drawImage->GetPosition(number + 3);
		rect.X = characterX;
		rect.Y = characterY + 20;
		drawImage->SetPosition(number + 3, rect.X, rect.Y);
		sceneManager->ReDraw(drawImage, number + 3);
		characterX = rect.X;
		characterY = rect.Y;
	}
	else {
		rect = drawImage->GetPosition(number + 3);
		drawImage->SetPosition(number + 3, characterX, characterY);
		sceneManager->ReDraw(drawImage, number + 3);
	}
}

void SceneManager::MoveRight(DrawImage * drawImage, SceneManager * sceneManager, int number)
{
	if (characterX < (mapWidth - WIDTH)) {
		rect = drawImage->GetPosition(number + 9);
		rect.X = characterX + 20;
		rect.Y = characterY;
		drawImage->SetPosition(number + 9, rect.X, rect.Y);
		sceneManager->ReDraw(drawImage, number + 9);
		characterX = rect.X;
		characterY = rect.Y;
	}
	else {
		rect = drawImage->GetPosition(number + 9);
		drawImage->SetPosition(number + 9, characterX, characterY);
		sceneManager->ReDraw(drawImage, number + 9);
	}
}

void SceneManager::MoveLeft(DrawImage * drawImage, SceneManager * sceneManager, int number)
{
	if (characterX > mapX) {
		rect = drawImage->GetPosition(number + 12);
		rect.X = characterX - 20;
		rect.Y = characterY;
		drawImage->SetPosition(number + 12, rect.X, rect.Y);
		sceneManager->ReDraw(drawImage, number + 12);
		characterX = rect.X;
		characterY = rect.Y;

	}
	else {
		rect = drawImage->GetPosition(number + 12);
		drawImage->SetPosition(number + 12, characterX, characterY);
		sceneManager->ReDraw(drawImage, number + 12);
	}
}

void SceneManager::SetPosition(DrawImage* drawImage)
{
	mapWidth = drawImage->GetClientArea().right;
	mapHeight = drawImage->GetClientArea().bottom;
	mapX = 0;
	mapY = 0;
	characterX = mapWidth / 2;
	characterY = mapHeight / 2;
	npcX = 100;
	npcY = 100;

	drawImage->SetPosition(0, Gdiplus::Rect(mapX, mapY, mapWidth, mapHeight));
	drawImage->SetPosition(1, npcX, npcY);

	for (int i = 3; i < (int)drawImage->GetImageCount(); i++)
	{
		drawImage->SetPosition(i, characterX, characterY);
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

	drawImage->AddImage(L"resource\\Dungeon.png");//15

}

void SceneManager::ReDraw(DrawImage* drawImage, int number)
{
	drawImage->Clear(0, 0, 0);
	for (int i = 0; i < 2; i++)
	{
		drawImage->Drawing(i);

	}
	drawImage->Drawing(number);
	drawImage->FlipBuffer();
}

void SceneManager::ReDrawDungeon(DrawImage * drawImage, int number)
{
	drawImage->Clear(0, 0, 0);

	drawImage->Drawing(15);
	drawImage->Drawing(2);
	drawImage->Drawing(number);
	drawImage->FlipBuffer();
}


