#include "SceneManager.h"
#include <conio.h>
#include <Windows.h>
#include <gdiplus.h>
#include <thread>
#include "LobbyBackgroundTexture.h"
#include "DungeonBackgroundTexture.h"
#include "time_util.h"
#include "NPCObject.h"

using namespace Gdiplus;

SceneManager::SceneManager()
{
	GdiplusStartupInput gdiplusStartupInput;
	gdiplusToken = NULL;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	system("mode con:cols=100 lines=50");

	hwnd = GetConsoleWindow();
	hdc = GetDC(hwnd);
	GetClientRect(hwnd, &clientArea);

	foreground = new Gdiplus::Graphics(hdc);
	bitmap = new Gdiplus::Bitmap(clientArea.right, clientArea.bottom);
	background = new Gdiplus::Graphics(bitmap);

	this->mainCharacter = new MainCharacter();
	this->mainCharacter->SetPosition(100, 100);

	this->lobbyBackground = new LobbyBackgroundTexture();
	this->lobbyBackground->SetSize(clientArea.right, clientArea.bottom);

	this->dungeonBackground = new DungeonBackgroundTexture();
	this->dungeonBackground->SetSize(clientArea.right, clientArea.bottom);

	this->currentBackground = lobbyBackground;

	NPCObject* npc1 = new NPCObject();
	npc1->SetPosition(300, 300);

	objectList.push_back((ObjectBase*)npc1);
	objectList.push_back((ObjectBase*)this->mainCharacter);
	this->loopThread = new std::thread(&SceneManager::Loop, this);
}

void SceneManager::Clear()
{
	Color color = { 0, 0, 0 };
	background->Clear(color);
}

void SceneManager::FlipBuffer()
{
	foreground->DrawImage(bitmap, 0, 0);
}

void SceneManager::DrawImage(Image * image, Rect rect)
{
	background->DrawImage(image, rect);
}

void SceneManager::Loop()
{
	long lastUpdateTime = 0;
	int deltaTime = 0;
	while (true) {

		if (lastUpdateTime == 0) {
			lastUpdateTime = GetCurrentTime();
			continue;
		}

		long currentTime = GetCurrentTime();
		deltaTime = currentTime - lastUpdateTime;
		lastUpdateTime = currentTime;
				
		UpdateObject(deltaTime);
		RedrawAll();

		Sleep(20);
	}
}

void SceneManager::UpdateObject(int deltaTime)
{
	for (int index = 0; index < (int)objectList.size(); index++) {
		objectList[index]->Update(deltaTime);
	}
}

void SceneManager::RedrawAll()
{
	Clear();

	DrawObject(this->currentBackground);

	for (int index = 0; index < (int)objectList.size(); index++) {
		DrawObject(objectList[index]);
	}

	FlipBuffer();
}

void SceneManager::DrawObject(ObjectBase* object)
{
	Image* image = object->GetImage();
	Rect rect = object->GetRect();

	DrawImage(image, rect);
}

void SceneManager::ChangeToDungeonBackground()
{
	currentBackground = dungeonBackground;
}

void SceneManager::ChangeToLobbyBackground()
{
	currentBackground = lobbyBackground;
}

void SceneManager::OnKeyLeft()
{
	mainCharacter->Move(Vector2D::Left);
}

void SceneManager::OnKeyRight()
{
	mainCharacter->Move(Vector2D::Right);
}

void SceneManager::OnKeyUp()
{
	mainCharacter->Move(Vector2D::Up);
}

void SceneManager::OnKeyDown()
{
	mainCharacter->Move(Vector2D::Down);
}

SceneManager::~SceneManager()
{
	delete foreground;
	delete background;
	delete bitmap;
	delete loopThread;

	for (int index = 0; index < (int)objectList.size(); index++) {
		delete objectList[index];
	}

	delete lobbyBackground;
	delete dungeonBackground;
}

