#include "SceneManager.h"
#include "DrawImage.h"



SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

void SceneManager::AddImage(DrawImage* drawImage)
{
	drawImage->AddImage(L"resource\\Background.png");//0

	drawImage->AddImage(L"resource\\Front_1.png");//1
	drawImage->AddImage(L"resource\\Front_2.png");//2
	drawImage->AddImage(L"resource\\Front_3.png");//3

	drawImage->AddImage(L"resource\\Rear_1.png");//4
	drawImage->AddImage(L"resource\\Rear_2.png");//5
	drawImage->AddImage(L"resource\\Rear_3.png");//6

	drawImage->AddImage(L"resource\\Right_1.png");//7
	drawImage->AddImage(L"resource\\Right_2.png");//8
	drawImage->AddImage(L"resource\\Right_3.png");//9

	drawImage->AddImage(L"resource\\Left_1.png");//10
	drawImage->AddImage(L"resource\\Left_2.png");//11
	drawImage->AddImage(L"resource\\Left_3.png");//12


}

void SceneManager::ReDraw(DrawImage * drawImage, int number)
{
	drawImage->Clear(0, 0, 0);

	drawImage->Drawing(0);
	drawImage->Drawing(number);
	drawImage->FlipBuffer();
}


