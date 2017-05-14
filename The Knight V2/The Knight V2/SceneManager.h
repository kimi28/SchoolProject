#include <Windows.h>
#include <gdiplus.h>
#include <vector>
#include "ObjectBase.h"
#include <thread>
#include "MainCharacter.h"
#include "DungeonBackgroundTexture.h"
#include "LobbyBackgroundTexture.h"

using namespace Gdiplus;

#pragma once
class SceneManager
{
private:
	Gdiplus::Graphics* foreground;
	Gdiplus::Graphics* background;
	Gdiplus::Bitmap* bitmap;

	ULONG_PTR gdiplusToken;

	HWND hwnd;
	HDC hdc;

	std::vector<ObjectBase*> objectList;

	std::thread* loopThread;

	MainCharacter* mainCharacter;

	LobbyBackgroundTexture* lobbyBackground;
	DungeonBackgroundTexture* dungeonBackground;

	ObjectBase* currentBackground;

	RECT clientArea;

	void Clear();
	void FlipBuffer();
	void DrawImage(Image* image, Rect rect);
	void Loop();
	void UpdateObject(int deltaTime);
	void RedrawAll();
	void DrawObject(ObjectBase* object);
public:
	SceneManager();
	~SceneManager();

	void ChangeToDungeonBackground();
	void ChangeToLobbyBackground();

	void OnKeyLeft();
	void OnKeyRight();
	void OnKeyUp();
	void OnKeyDown();
};

