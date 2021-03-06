#include "DungeonBackgroundTexture.h"

DungeonBackgroundTexture::DungeonBackgroundTexture(SceneManager* sceneManager) : ObjectBase(sceneManager)
{
	this->image = new Gdiplus::Image(L"resource\\Dungeon_Background.png");
	this->rect = { 0, 0, 0, 0 };

	this->rect.Width = image->GetWidth();
	this->rect.Height = image->GetHeight();
}


DungeonBackgroundTexture::~DungeonBackgroundTexture()
{
}
