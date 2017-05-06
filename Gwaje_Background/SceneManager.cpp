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

void SceneManager::RedrawMap()
{
	drawImage->AddImage(L"resource\\Background.png");
	drawImage->AddImage(L"resource\\Front_2.png");

	int width = drawImage->GetClientArea().right;
	int height = drawImage->GetClientArea().bottom;
	drawImage->SetPosition(0, Gdiplus::Rect(0, 0, width, height));
	drawImage->SetPosition(1, 100, 100);

	drawImage->Clear(0, 0, 0);
	for (int i = 0; i < drawImage->GetImageCount(); i++) {
		drawImage->Drawing(i);
	}

	drawImage->FlipBuffer();
}

void SceneManager::RedrwaNpc()
{
	


}

