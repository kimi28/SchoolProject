#include "SceneManager.h"

SceneManager::SceneManager(ObjectManager* objectManager)
{
	this->objectManager = objectManager;
	this->drawImage = new DrawImage();
}


SceneManager::~SceneManager()
{
	delete drawImage;
}

void SceneManager::AddImages(int number)
{
	drawImage->AddImage(L"resource\\Background.png");
	drawImage->AddImage(L"resource\\NPC.png");
	drawImage->AddImage(L"resource\\Front_1.png");
	drawImage->AddImage(L"resource\\Front_2.png");
	drawImage->AddImage(L"resource\\Front_3.png");

}

void SceneManager::RedrawMap()
{
	AddImages(0);
	
	int width = drawImage->GetClientArea().right;
	int height = drawImage->GetClientArea().bottom;
	drawImage->SetPosition(0, Gdiplus::Rect(0, 0, width, height));
	
	drawImage->Clear(0, 0, 0);

	drawImage->Drawing(0);

	drawImage->FlipBuffer();
}

void SceneManager::RedrawNpc()
{
	AddImages(1);
	drawImage->SetPosition(1, 100, 100);
	drawImage->Drawing(1);
	drawImage->FlipBuffer();

}

