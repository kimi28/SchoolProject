#include "SceneManager.h"
#include <conio.h>
#include <Windows.h>
#include <gdiplus.h>
#include <thread>
#include "LobbyBackgroundTexture.h"
#include "DungeonBackgroundTexture.h"
#include "time_util.h"
#include "NPCObject.h"
#include "Monster.h"

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

	characterX = (int)(clientArea.right - clientArea.left)*0.5f;
	characterY = (int)(clientArea.bottom - clientArea.top)*0.5f;
	this->mainCharacter = new MainCharacter();//mainCharacter�� �����Ҵ����� �ʱ�ȭ �Ѵ�.
	this->mainCharacter->SetPosition(characterX, characterY);//mainCharacter�� �̹����� ����� ��ǥ��ġ�� �����Ѵ�.

	this->lobbyBackground = new LobbyBackgroundTexture();//���� ����̹����� �����Ҵ����� �ʱ�ȭ�Ѵ�.
	this->lobbyBackground->SetSize(clientArea.right, clientArea.bottom);//���� ����̹����� ��»���� �����Ѵ�.

	this->dungeonBackground = new DungeonBackgroundTexture();//���� ����̹����� �����Ҵ����� �ʱ�ȭ�Ѵ�.
	this->dungeonBackground->SetSize(clientArea.right, clientArea.bottom);//���� ����̹����� ��»���� �����Ѵ�.

	this->currentBackground = lobbyBackground;//�켱 ����̹����� ��������̹����� �ʱ�ȭ�Ѵ�.

	NPCObject* npc1 = new NPCObject();//NPC�� �߰��ϰ� �ʱ�ȭ �Ѵ�.
	npc1->SetPosition(100, 200);//�ش� NPC�� �̹��� ��ǥ�� �����Ѵ�.

	this->monster = new Monster();
	srand(time(NULL));
	monsterX = rand() % (clientArea.right - monster->GetRect().Width) + 1;
	monsterY = rand() % (clientArea.bottom - monster->GetRect().Height) + 1;
	this->monster->SetPosition(monsterX, monsterY);

	objectList.push_back((ObjectBase*)npc1);//�߰��� NPC�� objectList�� push_back�Ͽ� �߰��Ѵ�.
	objectList.push_back((ObjectBase*)this->mainCharacter);//�߰��� ����ĳ���͸� objectList�� push_back�Ͽ� �߰��Ѵ�.
	objectList.push_back((ObjectBase*)this->monster);
	this->loopThread = new std::thread(&SceneManager::Loop, this);//������ �Լ��� �ʱ�ȭ �ϰ� ������ ���۽�Ų��.
}

void SceneManager::Clear()
{
	Color color = { 0, 0, 0 };//�÷��� �ҷ����� �ʱ�ȭ �Ѵ�.
	background->Clear(color);//��׶��带 �ҷ����� ����ȭ���� �����.
}

void SceneManager::FlipBuffer()
{
	foreground->DrawImage(bitmap, 0, 0);
}

void SceneManager::DrawImage(Image * image, Rect rect)
{
	background->DrawImage(image, rect);//���� �̹����� Rect��ǥ�� �̹����� �׸���.
}

void SceneManager::Loop()
{
	long lastUpdateTime = 0;//���� ������Ʈ�� �ð��� �����ϰ� �ʱ�ȭ �Ѵ�.
	int deltaTime = 0;//������Ʈ�� �ʿ��ϴ� �ð��� �����ϰ� �ʱ�ȭ �Ѵ�.
	while (true) {

		if (lastUpdateTime == 0) {
			lastUpdateTime = GetCurrentTime();
			continue;
		}//���� ���� ������Ʈ �ð��� ���� 0�� ���� �� Window�ð��� ���� ������Ʈ �ð��� �����Ѵ�.

		long currentTime = GetCurrentTime();// ���� �ð��� �����ϰ� Window�� ���� �ð��� ������ ������ �����Ѵ�.
		deltaTime = currentTime - lastUpdateTime;//���� �ð����� ����������Ʈ �ð��� ���ϸ� �׵��� �׼��� ���� �ð��� �����Ѵ�.
		lastUpdateTime = currentTime;//�׸��� ����ð��� ���� ������Ʈ �ð����� �����Ѵ�.

		UpdateObject(deltaTime);//������Ʈ�� �ð����� �����͸� ������Ʈ ��Ų��.
		RedrawAll();//������Ʈ �� �����ͷ� �̹����� �׸���.

		Sleep(20);//0.02�� ������ �ݺ� �����ϸ� �����͸� ������Ʈ �ϰ� �̹����� �ٽ� ����Ѵ�.
	}
}

void SceneManager::UpdateObject(int deltaTime)
{
	for (int index = 0; index < (int)objectList.size(); index++) {
		objectList[index]->Update(deltaTime);
	}//������Ʈ ����Ʈ�� ������Ʈ�� �ش�.
}

void SceneManager::RedrawAll()
{
	Clear();//���� ��׶��带 ���������� �����ش�.

	DrawObject(this->currentBackground);//���� �ʱ�ȭ�� ����̹����� �׸���.

	for (int index = 0; index < (int)objectList.size(); index++) {
		DrawObject(objectList[index]);
	}//������Ʈ ����Ʈ ���� ����� ��� �̹����� 1�� �����ϸ� ��� �׸���.

	FlipBuffer();
}

void SceneManager::DrawObject(ObjectBase* object)
{
	Image* image = object->GetImage();//������Ʈ ���̽��� �̹����� ������ ����  image�� �����Ѵ�.
	Rect rect = object->GetRect();//������Ʈ ���̽��� ��ǥ�� ���� image�� �����Ѵ�.

	DrawImage(image, rect);//������ �̹����� ��ǥ�� �׸���.
}

void SceneManager::ChangeToDungeonBackground()
{
	currentBackground = dungeonBackground;//���� ����̹����� �����ϰ��� �ϸ� �����̹����� ����� ������ currentBackground�� �����Ѵ�.
}

void SceneManager::ChangeToLobbyBackground()
{
	currentBackground = lobbyBackground;//���� ����̹����� �����ϰ��� �ϸ� �����̹����� ����� ������ currentBackground�� �����Ѵ�.
}

void SceneManager::OnKeyLeft()
{
	if (characterX > clientArea.left) {
	mainCharacter->Move(Vector2D::Left);//Ű���尡 �Է��� �Ǹ� ���� �ɸ��͸� �·� �̵��Ѵ�.
	}
	else {
		mainCharacter->Stop();
	}
}

void SceneManager::OnKeyRight()
{
	mainCharacter->Move(Vector2D::Right);//Ű���尡 �Է��� �Ǹ� ���� �ɸ��͸� ��� �̵��Ѵ�.
}

void SceneManager::OnKeyUp()
{
	mainCharacter->Move(Vector2D::Up);//Ű���尡 �Է��� �Ǹ� ���� �ɸ��͸� ������ �̵��Ѵ�.
}

void SceneManager::OnKeyDown()
{
	mainCharacter->Move(Vector2D::Down);//Ű���尡 �Է��� �Ǹ� ���� �ɸ��͸� �Ϸ� �̵��Ѵ�.
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
	//�� �����Ҵ����� ������ �����ڸ� ��� �Ҹ����ش�.
}

