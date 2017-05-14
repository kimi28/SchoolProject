#include "LobbyBackgroundTexture.h"



LobbyBackgroundTexture::LobbyBackgroundTexture()
{
	this->image = new Gdiplus::Image(L"resource\\Lobby_Background.png");
	this->rect = { 0, 0, 0, 0 };

	this->rect.Width = image->GetWidth();
	this->rect.Height = image->GetHeight();
}


LobbyBackgroundTexture::~LobbyBackgroundTexture()
{
}
