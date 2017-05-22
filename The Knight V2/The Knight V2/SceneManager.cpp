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
	this->mainCharacter = new MainCharacter(this);//mainCharacter를 동적할당으로 초기화 한다.
	this->mainCharacter->SetPosition(characterX, characterY);//mainCharacter의 이미지를 출력할 좌표위치를 지정한다.
	int mainCharacterWidth = mainCharacter->GetRect().Width;
	int mainCharacterHeight = mainCharacter->GetRect().Height;
	mainCharacterArea.left = characterX;
	mainCharacterArea.top = characterY;
	mainCharacterArea.right = mainCharacterWidth + characterX;
	mainCharacterArea.bottom = mainCharacterHeight + characterY;

	this->lobbyBackground = new LobbyBackgroundTexture(this);//마을 배경이미지를 동적할당으로 초기화한다.
	this->lobbyBackground->SetSize(clientArea.right, clientArea.bottom);//마을 배경이미지의 출력사이즈를 지정한다.

	this->dungeonBackground = new DungeonBackgroundTexture(this);//던전 배경이미지를 동적할당으로 초기화한다.
	this->dungeonBackground->SetSize(clientArea.right, clientArea.bottom);//던전 배경이미지의 출력사이즈를 지정한다.

	this->currentBackground = lobbyBackground;//우선 배경이미지를 마을배경이미지로 초기화한다.

	NPCObject* npc1 = new NPCObject(this);//NPC를 추가하고 초기화 한다.
	npc1->SetPosition(100, 200);//해당 NPC의 이미지 좌표를 지정한다.

	this->monster = new Monster(this);
	srand(time(NULL));
	monsterX = rand() % (clientArea.right - monster->GetRect().Width) + 1;
	monsterY = rand() % (clientArea.bottom - monster->GetRect().Height) + 1;
	this->monster->SetPosition(monsterX, monsterY);

	objectList.push_back((ObjectBase*)npc1);//추가된 NPC를 objectList에 push_back하여 추가한다.
	objectList.push_back((ObjectBase*)this->mainCharacter);//추가된 메인캐릭터를 objectList에 push_back하여 추가한다.
	objectList.push_back((ObjectBase*)this->monster);
	this->loopThread = new std::thread(&SceneManager::Loop, this);//스레드 함수를 초기화 하고 루프를 시작시킨다.
}

void SceneManager::Clear()
{
	Color color = { 0, 0, 0 };//컬러를 불랙으로 초기화 한다.
	background->Clear(color);//백그라운드를 불랙으로 기존화면을 지운다.
}

void SceneManager::FlipBuffer()
{
	foreground->DrawImage(bitmap, 0, 0);
}

void SceneManager::DrawImage(Image * image, Rect rect)
{
	background->DrawImage(image, rect);//받은 이미지와 Rect좌표로 이미지를 그린다.
}

void SceneManager::Loop()
{
	long lastUpdateTime = 0;//최종 업데이트한 시간을 정의하고 초기화 한다.
	int deltaTime = 0;//업데이트가 필요하는 시간을 정의하고 초기화 한다.
	while (true) {

		if (lastUpdateTime == 0) {
			lastUpdateTime = GetCurrentTime();
			continue;
		}//만약 최종 업데이트 시간의 값이 0과 같을 때 Window시간을 최종 업데이트 시간에 대입한다.

		long currentTime = GetCurrentTime();// 현재 시간을 정의하고 Window의 현재 시간을 정의한 변수에 대입한다.
		deltaTime = currentTime - lastUpdateTime;//현재 시간에서 최종업데이트 시간을 감하면 그동안 액션을 취한 시간을 대입한다.
		lastUpdateTime = currentTime;//그리고 현재시간을 최종 업데이트 시간으로 대입한다.

		UpdateObject(deltaTime);//업데이트할 시간내의 데이터를 업데이트 시킨다.
		RedrawAll();//업데이트 된 데이터로 이미지를 그린다.

		Sleep(20);//0.02초 단위로 반복 루프하며 데이터를 업데이트 하고 이미지를 다시 출력한다.
	}
}

void SceneManager::UpdateObject(int deltaTime)
{
	for (int index = 0; index < (int)objectList.size(); index++) {
		objectList[index]->Update(deltaTime);
	}//오브잭트 리스트를 업데이트해 준다.
}

void SceneManager::RedrawAll()
{
	Clear();//먼저 백그라운드를 검은색으로 지워준다.

	DrawObject(this->currentBackground);//현재 초기화된 배경이미지를 그린다.

	for (int index = 0; index < (int)objectList.size(); index++) {
		DrawObject(objectList[index]);
	}//오브잭트 리스트 내에 저장된 모든 이미지를 1씩 증가하며 모드 그린다.

	FlipBuffer();
}

void SceneManager::DrawObject(ObjectBase* object)
{
	Image* image = object->GetImage();//오브잭트 베이스에 이미지를 포인터 변수  image에 대입한다.
	Rect rect = object->GetRect();//오브잭트 베이스에 좌표를 변수 image에 대입한다.

	DrawImage(image, rect);//대입한 이미지와 좌표를 그린다.
}

void SceneManager::OnKeyLeft()
{

	Vector2D direction = Vector2D::Left;

	bool isCollision = CheckCollision(mainCharacter, direction);

	if (isCollision == false)
		mainCharacter->Move(direction);//키보드가 입력이 되면 메인 케릴터를 좌로 이동한다.

}

void SceneManager::OnKeyRight()
{
	Vector2D direction = Vector2D::Right;
	bool isCollision = CheckCollision(mainCharacter, direction);

	if (isCollision == false)
		mainCharacter->Move(direction);//키보드가 입력이 되면 메인 케릴터를 우로 이동한다.
}

void SceneManager::OnKeyUp()
{
	Vector2D direction = Vector2D::Up;
	bool isCollision = CheckCollision(mainCharacter, direction);

	if (isCollision == false)
		mainCharacter->Move(direction);//키보드가 입력이 되면 메인 케릴터를 상으로 이동한다.
}

void SceneManager::OnKeyDown()
{
	Vector2D direction = Vector2D::Down;
	bool isCollision = CheckCollision(mainCharacter, direction);

	if (isCollision == false)
		mainCharacter->Move(direction);//키보드가 입력이 되면 메인 케릴터를 하로 이동한다.
}

void SceneManager::ChangeBackgournd()
{
	if (currentBackground == lobbyBackground) {
		currentBackground = dungeonBackground;
	}
	else if (currentBackground == dungeonBackground) {
		currentBackground = lobbyBackground;
	}

}

bool SceneManager::CheckCollision(ObjectBase* obj, Vector2D direction)
{
	Vector2D circles = obj->GetCircles();
	int radius = obj->GetRadius();
	for (int index = 0; index < objectList.size(); index++) {
		ObjectBase* loopObj = objectList[index];
		if (obj == loopObj)
			continue;

		Vector2D aiCircles = loopObj->GetCircles();
		int aiRadius = loopObj->GetRadius();

		int deltaX = aiCircles.X - circles.X;
		int deltaY = aiCircles.Y - circles.Y;
		Vector2D distanceVector(deltaX, deltaY);
		double distance = distanceVector.Length();

		if (distance <= radius + aiRadius) {
			int angle = direction.angle(distanceVector);
			if (angle < 90)
				mainCharacter->Stop();
				return true;
		}
	}
	return false;
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
	//위 동적할당으로 생성된 생성자를 모두 소멸해준다.
}