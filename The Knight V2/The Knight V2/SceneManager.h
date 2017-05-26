#include <Windows.h>
#include <gdiplus.h>
#include <vector>
#include "ObjectBase.h"
#include <thread>
#include "MainCharacter.h"
#include "NPCObject.h"
#include "DungeonBackgroundTexture.h"
#include "LobbyBackgroundTexture.h"
#include <stdlib.h>
#include <time.h>
#include "Monster.h"
#pragma once

using namespace Gdiplus;

class WorldManager;
class SceneManager
{
private:
	Gdiplus::Graphics* foreground;
	Gdiplus::Graphics* background;
	Gdiplus::Bitmap* bitmap;

	ULONG_PTR gdiplusToken;

	HWND hwnd;
	HDC hdc;

	std::vector<ObjectBase*> objectList;//모든 곤솔창에 그려지는 모든 이미지를 저장하기 위해 SceneManager에서 objectList를 선언한다.

	std::thread* loopThread;//이미지를 지속적으로 그리기 위해 스레드 함수 선언.

	MainCharacter* mainCharacter;//메인 캐릭터 이미지를 그리기 위해 SceneManager에서 mainCharacter를 선언한다.
	Monster * monster;

	LobbyBackgroundTexture* lobbyBackground;//마을 이미지를 SceneManager에서 lobbyBackground를 선언한다.
	DungeonBackgroundTexture* dungeonBackground;//던전 이미지를 SceneManager에서 던전 배결선언한다.

	ObjectBase* currentBackground;//마을와 던전을 서로 교채를 위한 currentBackground를 선언한다.

	RECT clientArea;

	void Clear();//이미지 다시그리기 위해 기존 그린 이미지를 블랙으로 Clear하기.
	void FlipBuffer();//
	void DrawImage(Image* image, Rect rect);//이미지를 그리는 함수 선언.
	void Loop();//이미지를 액션이 없어도 반복으로 그리는 반복루프 함수 선언.
	void UpdateObject(int deltaTime);//ObjectList중 내용을 업데이트 하기위한 함수 선언.
	void RedrawAll();//ObjectList 저장된 모든 이미지를 그리기위한 함수선언.
	void DrawObject(ObjectBase* object);//ObjectList에 저장된 모든 이미지를 가져오기 위한 함수선언.
	int monsterX, monsterY;
	int characterX, characterY;
	bool isCollision;
public:
	SceneManager();
	~SceneManager();

	void OnKeyLeft();//메인 캐릭터가 키보드입력이 있을 때 이동방향 함수 선언.(좌)
	void OnKeyRight();//메인 캐릭터가 키보드입력이 있을 때 이동방향 함수 선언.(우)
	void OnKeyUp();//메인 캐릭터가 키보드입력이 있을 때 이동방향 함수 선언.(상)
	void OnKeyDown();//메인 캐릭터가 키보드입력이 있을 때 이동방향 함수 선언.(하)

	void ChangeBackgournd();
	bool CheckCollision(ObjectBase* obj, Vector2D direction);
};