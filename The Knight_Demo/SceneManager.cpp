#include "SceneManager.h"
#include "DrawImage.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

bool SceneManager::CheckCollision()
{
	rectNpc = { npcX, npcY, WIDTH, HEIGHT };
	rect = { characterX, characterY, WIDTH, HEIGHT };

	if (characterX <= (npcY + WIDTH)) {
		return true;
	}
	return false;
}

void SceneManager::MoveUp(DrawImage * drawImage, int number)
{
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

void SceneManager::MoveDown(DrawImage * drawImage, int number)
{

	if (characterY < (backgroudHeight - HEIGHT)) {
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

void SceneManager::MoveRight(DrawImage * drawImage, int number)
{
	if (characterX < (backgroudWidth - WIDTH)) {
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

void SceneManager::MoveLeft(DrawImage * drawImage, int number)
{
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

void SceneManager::SetPosition(DrawImage* drawImage)
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

void SceneManager::SetPositionDungeon(DrawImage * drawImage)
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

void SceneManager::AddImage(DrawImage* drawImage)
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


