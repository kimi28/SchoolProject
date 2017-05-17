#include "Monster.h"

void Monster::AddImage(WCHAR * path)
{
	Image* image = new Gdiplus::Image(path);
	this->rect = { 0, 0, 0, 0 };

	this->rect.Width = image->GetWidth();
	this->rect.Height = image->GetHeight();

	imageList.push_back(image);
}

Monster::Monster(char* name, int hp, int attack, int defence, int critical, int luck)
	:Character(name, hp, attack, defence, critical, luck)
{
	AddImage(L"resource\\Monster_1.png");//0
	AddImage(L"resource\\Monster_2.png");//1
	this->currentImageIndex = 0;
	this->image = imageList[currentImageIndex];
}

Monster::~Monster()
{
}
