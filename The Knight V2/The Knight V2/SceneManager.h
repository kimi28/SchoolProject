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

class SceneManager
{
private:
	Gdiplus::Graphics* foreground;
	Gdiplus::Graphics* background;
	Gdiplus::Bitmap* bitmap;

	ULONG_PTR gdiplusToken;

	HWND hwnd;
	HDC hdc;

	std::vector<ObjectBase*> objectList;//��� ���â�� �׷����� ��� �̹����� �����ϱ� ���� SceneManager���� objectList�� �����Ѵ�.

	std::thread* loopThread;//�̹����� ���������� �׸��� ���� ������ �Լ� ����.

	MainCharacter* mainCharacter;//���� ĳ���� �̹����� �׸��� ���� SceneManager���� mainCharacter�� �����Ѵ�.
	Monster * monster;

	LobbyBackgroundTexture* lobbyBackground;//���� �̹����� SceneManager���� lobbyBackground�� �����Ѵ�.
	DungeonBackgroundTexture* dungeonBackground;//���� �̹����� SceneManager���� ���� ��ἱ���Ѵ�.

	ObjectBase* currentBackground;//������ ������ ���� ��ä�� ���� currentBackground�� �����Ѵ�.

	RECT clientArea;

	void Clear();//�̹��� �ٽñ׸��� ���� ���� �׸� �̹����� ������ Clear�ϱ�.
	void FlipBuffer();//
	void DrawImage(Image* image, Rect rect);//�̹����� �׸��� �Լ� ����.
	void Loop();//�̹����� �׼��� ��� �ݺ����� �׸��� �ݺ����� �Լ� ����.
	void UpdateObject(int deltaTime);//ObjectList�� ������ ������Ʈ �ϱ����� �Լ� ����.
	void RedrawAll();//ObjectList ����� ��� �̹����� �׸������� �Լ�����.
	void DrawObject(ObjectBase* object);//ObjectList�� ����� ��� �̹����� �������� ���� �Լ�����.
	int monsterX, monsterY;
	int characterX, characterY;
public:
	SceneManager();
	~SceneManager();

	void ChangeToDungeonBackground();//����� �����̶�� �������� ��ü�� ���� ����̹��� ��ü �Լ�.
	void ChangeToLobbyBackground();//����� �����̶�� �������� ��ü�� ���� ����̹��� ��ü �Լ�.

	void OnKeyLeft();//���� ĳ���Ͱ� Ű�����Է��� ���� �� �̵����� �Լ� ����.(��)
	void OnKeyRight();//���� ĳ���Ͱ� Ű�����Է��� ���� �� �̵����� �Լ� ����.(��)
	void OnKeyUp();//���� ĳ���Ͱ� Ű�����Է��� ���� �� �̵����� �Լ� ����.(��)
	void OnKeyDown();//���� ĳ���Ͱ� Ű�����Է��� ���� �� �̵����� �Լ� ����.(��)

	void ChangeBackgournd() {
		if (currentBackground == lobbyBackground) {
			ChangeToDungeonBackground();
		}
		else if (currentBackground == dungeonBackground) {
			ChangeToLobbyBackground();
		}
	}
};