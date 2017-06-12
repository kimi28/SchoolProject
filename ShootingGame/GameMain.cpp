#include "stdafx.h"
#include "GameMain.h"
#include "DrawRect.h"
#include "Intersect.h"


GameMain::GameMain(HINSTANCE hInstance, LPCWSTR className, LPCSTR lpCmdLine, int nCmdShow)
	: DxWindow(hInstance, className, lpCmdLine, nCmdShow)
	, prevTime1(0)
	, prevTime2(0)
	, prevTime3(0)
{
}


GameMain::~GameMain()
{
}

void GameMain::Initialize()
{
	POINT wCoord = { 0 , 0 };
	POINT wSize = { winSize.x, winSize.y };
	winRect = new DrawRect(device, wCoord, wSize);
	winRect->Initialize();

	POINT mCoord = { winSize.x*0.5f, winSize.y - 55 };
	POINT mSize = { 50, 50 };
	mainRect = new DrawRect(device, mCoord, mSize);
	mainRect->Initialize();

	for (int i = 0; i < 10; i++) {
		POINT wellCoord = { i * 150, 350 };
		POINT wellSize = { 100, 50 };
		wellRect[i] = new DrawRect(device, wellCoord, wellSize);
		wellRect[i]->Initialize();
	}

	for (int i = 0; i < 4; i++) {
		POINT moveCoord = { (i * 50 + winSize.x*0.5f), (i * 70 + 10) };
		POINT moveSize = { 50, 50 };
		monsterRect[i] = new DrawRect(device, moveCoord, moveSize);
		monsterRect[i]->Initialize();
	}
}

void GameMain::Destroy()
{
	winRect->Destroy();
	SAFE_DELETE(winRect);

	mainRect->Destroy();
	SAFE_DELETE(mainRect);

	for (int i = 0; i < (int)bulletList.size(); i++) {
		bulletList[i]->Destroy();
		bulletList.clear();
	}

	for (int i = 0; i < 10; i++) {
		wellRect[i]->Destroy();
		SAFE_DELETE(wellRect[i]);
	}

	for (int i = 0; i < 4; i++) {
		monsterRect[i]->Destroy();
		SAFE_DELETE(monsterRect[i]);
	}

	Keyboard::DeleteInstance();
	Mouse::DeleteInstance();
}

void GameMain::Update()
{
	if (mainRect->GetCoord().x > winRect->GetCoord().x && mainRect->GetCoord().x < winRect->GetSize().x - mainRect->GetSize().x) {
		POINT coord = mainRect->GetCoord();
		if (Keyboard::GetInstance()->KeyPress(VK_RIGHT)) {
			coord.x += 10;

			if (coord.x >= (winRect->GetSize().x - mainRect->GetSize().x)) {
				coord.x -= 10;
			}
		}
		else if (Keyboard::GetInstance()->KeyPress(VK_LEFT)) {
			coord.x -= 10;

			if (coord.x <= winRect->GetCoord().x) {
				coord.x += 10;
			}
		}
		mainRect->SetCoord(coord);
	}

	DWORD curTime = timeGetTime();
	POINT coord1 = monsterRect[0]->GetCoord();
	POINT coord2 = monsterRect[1]->GetCoord();
	POINT coord3 = monsterRect[2]->GetCoord();
	POINT coord4 = monsterRect[3]->GetCoord();
	if (prevTime1 == 0 || (curTime - prevTime1) > 200) {
		if (coord1.x > winRect->GetCoord().x && coord1.x < winRect->GetSize().x - monsterRect[0]->GetSize().x) {
			static int count1 = 0;
			if (count1 == 0) {
				coord1.x += 15;
				if (coord1.x >= 972)
					count1 = 1;
			}
			if (count1 == 1) {
				coord1.x -= 15;
				if (coord1.x <= 2)
					count1 = 0;
			}
		}
		if (coord2.x > winRect->GetCoord().x && coord2.x < winRect->GetSize().x - monsterRect[1]->GetSize().x) {
			static int count2 = 0;
			if (count2 == 0) {
				coord2.x -= 10;
				if (coord2.x <= 1)
					count2 = 1;
			}
			if (count2 == 1) {
				coord2.x += 10;
				if (coord2.x >= 972)
					count2 = 0;
			}
		}
		if (coord3.x > winRect->GetCoord().x && coord3.x < winRect->GetSize().x - monsterRect[2]->GetSize().x) {
			static int count3 = 0;
			if (count3 == 0) {
				coord3.x += 10;
				if (coord3.x >= 972)
					count3 = 1;
			}
			if (count3 == 1) {
				coord3.x -= 10;
				if (coord3.x <= 2)
					count3 = 0;
			}
		}
		if (coord4.x > winRect->GetCoord().x && coord4.x < winRect->GetSize().x - monsterRect[3]->GetSize().x) {
			static int count4 = 0;
			if (count4 == 0) {
				coord4.x -= 15;
				if (coord4.x <= 1)
					count4 = 1;
			}
			if (count4 == 1) {
				coord4.x += 15;
				if (coord4.x >= 962)
					count4 = 0;
			}
		}
		monsterRect[0]->SetCoord(coord1);
		monsterRect[1]->SetCoord(coord2);
		monsterRect[2]->SetCoord(coord3);
		monsterRect[3]->SetCoord(coord4);
	}

	if (Keyboard::GetInstance()->KeyDown(VK_SPACE)) {
		DrawRect* bullet;
		POINT bCoord = { mainRect->GetCoord().x + 20 ,mainRect->GetCoord().y };
		POINT bsize = { 10 ,10 };
		bullet = new DrawRect(device, bCoord, bsize);
		bullet->Initialize();
		bulletList.push_back(bullet);
	}

	if (prevTime2 == 0 || (curTime - prevTime2) > 2)
	{
		for (int i = 0; i < (int)bulletList.size(); i++)
		{
			POINT coord = bulletList[i]->GetCoord();
			coord.y -= 10;

			for (int x = 0; x < 10; x++)
			{
				if (Intersect::IsContainRect(NULL, bulletList[i], wellRect[x]) == true) //충돌시 화면 밖으로 날림
				{
					
					bulletList[i]->SetSize({ 0,0 });
					wellRect[x]->SetColor(0xFFFF0000);
				}

				if (prevTime3 == 0 || (curTime - prevTime3) > 1000)
				{
					for (int x = 0; x < 10; x++)
					{
						DWORD color = wellRect[x]->GetColor();

						color = (color != 0xFF000000) ? 0xFF000000 : 0xFFFF0000;
					}

					prevTime3 = curTime;
				}
			}

			for (int x = 0; x < 4; x++) {
				if (Intersect::IsContainRect(NULL, bulletList[i], monsterRect[x]) == true)
				{
					bulletList[i]->SetCoord(coord);
					bulletList[i]->SetSize({ 0,0 });
					monsterRect[x]->SetColor(0xFFFF0000);
					monsterRect[x]->SetSize({ 0,0 });
					//coord.x = 2500;
					//prevTimeEne[x] = timeGetTime();
					//arrInterEne[x] = true;
				}
			}
			bulletList[i]->SetCoord(coord);
		}
		prevTime2 = curTime;
	}

	winRect->Update();
	mainRect->Update();

	for (int i = 0; i < 10; i++) {
		wellRect[i]->Update();
	}
	for (int i = 0; i < 4; i++) {
		monsterRect[i]->Update();
	}
	for (int i = 0; i < (int)bulletList.size(); i++) {
		bulletList[i]->Update();
	}

	Keyboard::GetInstance()->Update();
	Mouse::GetInstance()->Update();
}

void GameMain::Render()
{
	if (device == NULL)
		return;

	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(1, 1, 1, 1), 1.0f, 0);

	device->BeginScene();

	winRect->Render();
	mainRect->Render();
	for (int i = 0; i < 10; i++) {
		wellRect[i]->Render();
	}
	for (int i = 0; i < 4; i++) {
		monsterRect[i]->Render();
	}
	for (int i = 0; i < (int)bulletList.size(); i++) {
		bulletList[i]->Render();
	}

	device->EndScene();
	device->Present(0, 0, 0, 0);
}
